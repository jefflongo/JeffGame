#ifndef PLAYER_H_
#define PLAYER_H_

#include <fstream>
#include "SFML/Graphics.hpp"

class Controller;
class PlayerState;
class Stage;

class Player
{
public:
	enum class Direction { Left, Right };

	Player();
	Player(Controller* controller, Direction direction, float xOffset);

	void update(Stage& stage);

	void setState(PlayerState* state);
	void setNextState(PlayerState* state);
	void checkForStateChange();
	void setPos(float x, float y);
	void setVelo(float x, float y);
	void setGrounded(bool onGround);
	void setAnimation(std::string animID, int widthOffset = 0, int heightOffset = 0, float angle = 0);
	void setOnScreenState(std::string text);

	sf::Vector2f getPos() const { return pos_; }
	sf::Vector2f getVelo() const { return velo_; }
	Direction getDirection() const { return direction_; }
	bool isOnGround() const { return onGround_; }

	void changeDirection();
	void jump();
	void fastFall();
	void move();
	void decelOnGround();
	void applyGravity();
	void limitSpeed();
	void checkForCollisions(Stage& stage);

	void render(sf::RenderWindow& window, bool debugMode);

private:
	struct Coords
	{
		unsigned int x, y, width, height;
	};

	PlayerState* state_ = nullptr, *nextState_ = nullptr;
	Controller* controller_;
	std::ifstream coordsFile_;
	Direction direction_;

	sf::Vector2f pos_, velo_;
	sf::Texture sheet_;
	sf::Sprite playerSprite_;
	sf::RectangleShape playerBox_;
	sf::Font font_;
	sf::Text playerstateText_;

	bool onGround_ = false;

	// Put these in a struct?
	const float ACCEL = 8.0f;
	const float GROUND_FRICTION = 0.6f;
	const float JUMP_SPEED = 50.0f;
	const float GRAVITY = 1.8f;
	const float TERMINAL_WALK_VELOCITY = 13.1f;
	const float TERMINAL_RUN_VELOCITY = 18.0f;
	const float TERMINAL_JUMP_VELOCITY = 19.0f;
	const float TERMINAL_FALL_VELOCITY = 20.0f;
	const float AIR_FRICTION = 0.2f;
};

#endif // PLAYER_H_