#include "Player.h"

#include <iostream>
#include <string>
#include <sstream>
#include "Globals.h"
#include "Controller.h"
#include "PlayerState.h"
#include "Stage.h"

Player::Player() {}
Player::Player(Controller* controller, Direction direction, float xOffset)
{
	// static int players++;
	controller_ = controller;

	coordsFile_.open("res/images/spritesheet_fox.txt");
	if (!coordsFile_)
	{
		std::cout << "Failed to open sprite sheet coordinates file.\n";
	}

	if (!sheet_.loadFromFile("res/images/spritesheet_fox.png"))
	{
		std::cout << "Failed to open sprite sheet.\n";
	}
	playerSprite_.setTexture(sheet_);

	font_.loadFromFile("res/fonts/PressStart2P.ttf");
	playerstateText_.setFont(font_);
	playerstateText_.setPosition(20, 20);

	// ugly
	playerSprite_.setTextureRect(sf::IntRect(530, 435, 25, 37));

	playerBox_.setSize(sf::Vector2f(playerSprite_.getGlobalBounds().width, playerSprite_.getGlobalBounds().height));
	playerBox_.setOrigin(0.5f*playerBox_.getGlobalBounds().width, 0.5f*playerBox_.getGlobalBounds().height);
	playerBox_.setScale(2.3f, 2.3f);
	playerBox_.setPosition(xOffset, static_cast<float>(Globals::WINDOW_HEIGHT) - 100);
	playerBox_.setFillColor(sf::Color(255, 255, 0, 75));

	playerSprite_.setOrigin(0.5f*playerSprite_.getGlobalBounds().width, 0.5f*playerSprite_.getGlobalBounds().height);
	playerSprite_.setScale(playerBox_.getScale());
	playerSprite_.setPosition(playerBox_.getPosition());

	direction_ = direction;
	if (direction_ == Direction::Left)
	{
		playerSprite_.scale(-1, 1);
	}
}

void Player::update(Stage& stage)
{
	checkForStateChange();
	pos_ = playerBox_.getPosition();
	if (controller_ != nullptr)
	{
		controller_->update();
	}
	state_->handleInput(*this, controller_);
	state_->update(*this, controller_);
	state_->animate(*this);
	applyGravity();
	limitSpeed();
	pos_ += velo_;
	checkForCollisions(stage);
	playerBox_.setPosition(pos_);
	playerSprite_.setPosition(playerBox_.getPosition());
}

// this is only used to initialize the first state
void Player::setState(PlayerState* state)
{
	if (state_ != nullptr)
	{
		state_->destroy(*this);
		delete state_;
	}
	state_ = state;
	if (state_ != nullptr)
	{
		state_->init(*this);
	}
}

// make sure the following 2 methods have no memory leaks
// this method ensures the state change occurs at the beginning of the next frame
void Player::setNextState(PlayerState* state)
{
	// to avoid state->update() from overriding state->handleInput()
	if (nextState_ == nullptr)
	{
		nextState_ = state;
	}
}

void Player::checkForStateChange()
{
	if (state_ != nullptr && nextState_ != nullptr)
	{
		state_->destroy(*this);

		delete state_;
		state_ = nextState_;
		nextState_ = nullptr;

		state_->init(*this);
	}
}

void Player::setPos(float x, float y)
{
	pos_.x = x;
	pos_.y = y;
}

void Player::setVelo(float x, float y)
{
	velo_.x = x;
	velo_.y = y;
}

void Player::setGrounded(bool onGround)
{
	onGround_ = onGround;
}

void Player::setAnimation(std::string animID, int widthOffset, int heightOffset, float angle)
{
	std::stringstream stream;
	std::string line;
	Coords coords;

	// Find the index of the animation ID
	while (getline(coordsFile_, line))
	{
		if (line.find(animID) != std::string::npos)
		{
			break;
		}
	}

	if (coordsFile_.eof())
	{
		std::cout << "ERROR: Invalid Animation.\n";
		return;
	}
	else
	{
		coordsFile_.seekg(0);
	}

	// Truncate to the coordinates
	for (unsigned int i = 0; i < line.length(); i++)
	{
		if (line[i] == '=')
		{
			line = line.substr(i + 2, line.length());
			break;
		}
	}

	// Store the coordinates in a struct
	stream << line;
	stream >> coords.x >> coords.y >> coords.width >> coords.height;

	// why local bounds?
	playerSprite_.setTextureRect(sf::IntRect(coords.x, coords.y, coords.width, coords.height));
	playerSprite_.setOrigin(0.5f*playerSprite_.getLocalBounds().width, 0.5f*playerSprite_.getLocalBounds().height);
	playerBox_.setSize(sf::Vector2f(static_cast<float>(coords.width) + widthOffset, static_cast<float>(coords.height) + heightOffset));
	playerBox_.setOrigin(0.5f*playerBox_.getLocalBounds().width, 0.5f*playerBox_.getLocalBounds().height);
	playerBox_.setRotation(angle);
}

void Player::setOnScreenState(std::string text)
{
	playerstateText_.setString(text);
}

sf::Vector2f Player::getPos() const 
{
	return pos_;
}

sf::Vector2f Player::getVelo() const 
{ 
	return velo_; 
}

Player::Direction Player::getDirection() const 
{
	return direction_; 
}

bool Player::isOnGround() const 
{ 
	return onGround_; 
}

void Player::changeDirection()
{
	if (onGround_)
	{
		if (direction_ == Direction::Right)
		{
			direction_ = Direction::Left;
		}
		else
		{
			direction_ = Direction::Right;
		}
		playerBox_.scale(-1, 1);
		playerSprite_.scale(-1, 1);
	}
}

void Player::jump()
{
	velo_.y -= JUMP_SPEED;
	onGround_ = false;
}

void Player::fastFall()
{
	if (velo_.y >= 0)
	{
		velo_.y = TERMINAL_FALL_VELOCITY;
	}
}

void Player::move()
{
	float analogInfluence = controller_->getStickPositionPercentage(StickName::CONTROL_STICK).x / 100;
	if (onGround_)
	{
		velo_.x += ACCEL*analogInfluence;
	}
	else
	{
		velo_.x += ACCEL*AIR_FRICTION*analogInfluence;
	}
}

void Player::decelOnGround()
{
	if (onGround_)
	{
		velo_.x *= GROUND_FRICTION;
		if (velo_.x > -0.001 && velo_.x < 0.001)
		{
			velo_.x = 0;
		}
	}
}

void Player::applyGravity()
{
	if (!onGround_)
	{
		velo_.y += GRAVITY;
	}
}

void Player::limitSpeed()
{
	if (velo_.x > TERMINAL_RUN_VELOCITY)
	{
		velo_.x = TERMINAL_RUN_VELOCITY;
	}

	if (velo_.x < -TERMINAL_RUN_VELOCITY)
	{
		velo_.x = -TERMINAL_RUN_VELOCITY;
	}

	if (velo_.y < -TERMINAL_JUMP_VELOCITY)
	{
		velo_.y = -TERMINAL_JUMP_VELOCITY;
	}

	if (velo_.y > TERMINAL_FALL_VELOCITY)
	{
		velo_.y = TERMINAL_FALL_VELOCITY;
	}
}

void Player::checkForCollisions(Stage& stage)
{
	// potential problems with intersecting a platform and the ground simultaneously
	int collisionIndexPlatform = stage.platformCollision(playerBox_, pos_), collisionIndexGround = stage.groundCollision(playerBox_, pos_);

	if (collisionIndexPlatform >= 0)
	{
		// collision from above
		// TODO: add the other cases
		// on ground if the playerbox is above the surface and landing happens iff the playerbox is not fast falling
		if (pos_.y <= stage.getPermeableObject(collisionIndexPlatform).getPosition().y && velo_.y >= 0 && velo_.y != TERMINAL_FALL_VELOCITY)
		{
			velo_.y = 0;
			onGround_ = true;
			// stage position - half of the height of the stage - half of the height of the player plus an offset to avoid animations being in the air
			pos_.y = stage.getPermeableObject(collisionIndexPlatform).getPosition().y - 0.5f*stage.getPermeableObject(collisionIndexPlatform).getGlobalBounds().height - 0.5f*playerBox_.getGlobalBounds().height + 15;
		}
	}
	else if (collisionIndexGround >= 0)
	{
		velo_.y = 0;
		// collision from above
		// TODO: add the other cases
		// on ground if the playerbox is above the surface and landing happens iff the playerbox is moving downward
		if (pos_.y < stage.getCollidableObject(collisionIndexGround).getPosition().y && velo_.y >= 0)
		{
			onGround_ = true;
			// stage position - half of the height of the stage - half of the height of the player plus an offset to avoid animations being in the air
			pos_.y = stage.getCollidableObject(collisionIndexGround).getPosition().y - 0.5f*stage.getCollidableObject(collisionIndexGround).getGlobalBounds().height - 0.5f*playerBox_.getGlobalBounds().height + 15;
		}
	}
	else
	{
		onGround_ = false;
	}
}

void Player::render(sf::RenderWindow& window, bool debugMode)
{
	window.draw(playerSprite_);
	if (debugMode)
	{
		window.draw(playerBox_);
		window.draw(playerstateText_);
	}
}