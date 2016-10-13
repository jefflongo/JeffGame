#include "IdleState.h"

#include <iostream>
#include "SFML/Graphics.hpp"
#include "../Globals.h"
#include "../Player.h"
#include "../Controller.h"

#include "ForwardSpecialState.h"
#include "JabState.h"
#include "UpSmashState.h"
#include "DownSmashState.h"
#include "ForwardSmashState.h"
#include "UpTiltState.h"
#include "DownTiltState.h"
#include "ForwardTiltState.h"
#include "JumpSquatState.h"
#include "GrabState.h"
#include "TauntState.h"
#include "DashState.h"
#include "SquatState.h"
#include "TurnState.h"

void IdleState::init(Player& player)
{
	std::cout << "Entered idle state.\n";
	player.setOnScreenState("Idle");
}

void IdleState::handleInput(Player& player, Controller* controller)
{
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::A))
	{
		player.setNextState(new JabState());
		return;
	}

	if (controller == nullptr)
	{
		return;
	}
	
	sf::Vector2f controlStickPos = controller->getStickPosition(StickName::CONTROL_STICK);
	sf::Vector2f cStickPos = controller->getStickPosition(StickName::C_STICK);
	// Hierarchy of button press priority: START > Z > B > A > C_STICK > L/R > X/Y > D_PAD
	// Z presses
	if (controller->buttonPressed(ButtonName::Z))
	{
		player.setNextState(new GrabState());
		return;
	}
	// B presses
	else if (controller->buttonPressed(ButtonName::B))
	{
		if (controlStickPos.x >= 0.60)
		{
			if (player.getDirection() == Player::Direction::Left)
			{
				player.changeDirection();
			}
			player.setNextState(new ForwardSpecialState());
			return;
		}
		else if (controlStickPos.x <= -0.60)
		{
			if (player.getDirection() == Player::Direction::Right)
			{
				player.changeDirection();
			}
			player.setNextState(new ForwardSpecialState());
			return;
		}
		else if (controlStickPos.y <= -0.55)
		{
			std::cout << "up b\n";
			return;
		}
		else if (controlStickPos.y >= 0.55)
		{
			std::cout << "down b\n";
			return;
		}
		else
		{
			std::cout << "neutral b\n";
			return;
		}
	}
	// A presses
	else if (controller->buttonPressed(ButtonName::A))
	{
		if (controller->buttonPressed(ButtonName::L) || controller->buttonPressed(ButtonName::R))
		{
			player.setNextState(new GrabState());
			return;
		}
		else if (controlStickPos.x >= 0.80)
		{
			if (controller->getFramesSinceDirectionChange(StickName::CONTROL_STICK).x <= 4)
			{
				if (player.getDirection() == Player::Direction::Left)
				{
					player.changeDirection();
				}
				player.setNextState(new ForwardSmashState());
				return;
			}
		}
		else if (controlStickPos.x <= -0.80)
		{
			if (controller->getFramesSinceDirectionChange(StickName::CONTROL_STICK).x <= 4)
			{
				if (player.getDirection() == Player::Direction::Right)
				{
					player.changeDirection();
				}
				player.setNextState(new ForwardSmashState());
				return;
			}
		}
		else if (controlStickPos.y <= -0.66)
		{
			if (controller->getFramesSinceDirectionChange(StickName::CONTROL_STICK).y <= 4)
			{
				player.setNextState(new UpSmashState());
				return;
			}
		}
		else if (controlStickPos.y >= 0.66)
		{
			if (controller->getFramesSinceDirectionChange(StickName::CONTROL_STICK).y <= 4)
			{
				player.setNextState(new DownSmashState());
				return;
			}
		}
		else if (controlStickPos.x >= abs(0.7*controlStickPos.y))
		{
			if (player.getDirection == Player::Direction::Right)
			{
				player.setNextState(new ForwardTiltState());
				return;
			}
			else
			{
				player.setNextState(new JabState());
				return;
			}
		}
		else if (controlStickPos.x <= -abs(0.7*controlStickPos.y))
		{
			if (player.getDirection == Player::Direction::Left)
			{
				player.setNextState(new ForwardTiltState());
				return;
			}
			else
			{
				player.setNextState(new JabState());
				return;
			}
		}
		else if (controlStickPos.y < 0)
		{
			player.setNextState(new UpTiltState());
			return;
		}
		else if (controlStickPos.y > 0)
		{
			player.setNextState(new DownTiltState());
			return;
		}
		else
		{
			player.setNextState(new JabState());
			return;
		}
	}
	// TODO: C-stick preeses
	// L/R presses
	else if (controller->buttonPressed(ButtonName::L) || controller->buttonPressed(ButtonName::R))
	{
		// TODO: Add analog shielding eventually
		std::cout << "shield\n";
		return;
	}
	// X/Y presses
	else if (controller->buttonPressed(ButtonName::X) || controller->buttonPressed(ButtonName::Y))
	{
		player.setNextState(new JumpSquatState());
		return;
	}
	// D-Pad presses
	else if (controller->buttonPressed(ButtonName::D_PAD_UP))
	{
		player.setNextState(new TauntState());
		return;
	}
	// Control Stick presses
	else if (controlStickPos.y <= -0.66)
	{
		if (controller->getFramesSinceDirectionChange(StickName::CONTROL_STICK).y <= 4)
		{
			player.setNextState(new JumpSquatState());
			return;
		}
	}
	else if (controlStickPos.y >= 0.70)
	{
		player.setNextState(new SquatState());
		return;
	}
	else if (controlStickPos.x >= 0.80)
	{
		if (controller->getFramesSinceDirectionChange(StickName::CONTROL_STICK).x <= 4)
		{
			if (player.getDirection() == Player::Direction::Right)
			{
				player.setState(new DashState());
				return;
			}
			else
			{
				// Smash Turn
				player.setState(new TurnState());
				return;
			}
		}
	}
	else if (controlStickPos.x <= -0.80)
	{
		if (controller->getFramesSinceDirectionChange(StickName::CONTROL_STICK).x <= 4)
		{
			if (player.getDirection() == Player::Direction::Left)
			{
				player.setState(new DashState());
				return;
			}
			else
			{
				// Smash Turn
				player.setState(new TurnState());
				return;
			}
		}
	}
	else if (controlStickPos.x > 0)
	{
		if (player.getDirection() == Player::Direction::Right)
		{
			std::cout << "walk.\n";
			return;
		}
		else
		{
			// Smash Turn
			player.setState(new TurnState());
			return;
		}
	}
	else if (controlStickPos.x < 0)
	{
		if (player.getDirection() == Player::Direction::Left)
		{
			std::cout << "walk.\n";
			return;
		}
		else
		{
			// Smash Turn
			player.setState(new TurnState());
			return;
		}
	}
}

void IdleState::update(Player& player, Controller* controller)
{
	player.decelOnGround();
}

void IdleState::animate(Player& player)
{
	if (animFrame_ == 1)
	{
		player.setAnimation("idle_01");
	}
	else if (animFrame_ == 11)
	{
		player.setAnimation("idle_02");
	}
	else if (animFrame_ == 21)
	{
		player.setAnimation("idle_03");
	}
	else if (animFrame_ == 31)
	{
		player.setAnimation("idle_04");
	}
	else if (animFrame_ == 41)
	{
		player.setAnimation("idle_05");
	}
	else if (animFrame_ == 51)
	{
		player.setAnimation("idle_06");
	}
	else if (animFrame_ >= 60)
	{
		animFrame_ = 0;
	}
	animFrame_++;
}

void IdleState::destroy(Player& player)
{
	player.setOnScreenState("");
}