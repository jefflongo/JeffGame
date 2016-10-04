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

	// L/R presses
	if (controller->buttonPressed(ButtonName::L) || controller->buttonPressed(ButtonName::R))
	{
		// TODO: Add analog shielding eventually
		if (controller->buttonPressed(ButtonName::A))
		{
			player.setNextState(new GrabState());
			return;
		}
		else
		{
			std::cout << "shield\n";
			return;
		}
	}
	// B presses
	else if (controller->buttonPressed(ButtonName::B))
	{
		if (controller->getStickPosition(StickName::CONTROL_STICK).y < -55 && 
		Globals::valueBetween(controller->getStickPosition(StickName::CONTROL_STICK).x, -55, 55) ||
		controller->getStickPosition(StickName::CONTROL_STICK).y < -75 &&
		Globals::valueBetween(controller->getStickAngle(StickName::CONTROL_STICK), 53, 127))
		{
			std::cout << "up b\n";
			return;
		}
		else if (controller->axisPercentageGreaterThan(Axis::Y, 55) && controller->axisPercentageBetween(Axis::X, -55, 55) ||
			     controller->axisPercentageGreaterThan(Axis::Y, 75) && controller->controlStickAngleBetween(233, 307))
		{
			std::cout << "down b\n";
			return;
		}
		else if (controller->axisPercentageGreaterThan(Axis::X, 55))
		{
			if (controller->controlStickAngleBetween(0, 54) || controller->controlStickAngleBetween(306, 360))
			{
				if (player.getDirection() == Player::Direction::Left)
				{
					player.changeDirection();
				}
				player.setNextState(new ForwardSpecialState());
				return;
			}
		}
		else if (controller->axisPercentageLessThan(Axis::X, -55))
		{
			if (controller->controlStickAngleBetween(126, 234))
			{
				if (player.getDirection() == Player::Direction::Right)
				{
					player.changeDirection();
				}
				player.setNextState(new ForwardSpecialState());
				return;
			}
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
		if (controller->axisPercentageLessThan(Axis::Y, -66))
		{
			if (controller->controlStickAngleBetween(43, 137))
			{
				if (controller->cardinalDirectionChange(Axis::Y, 4))
				{
					player.setNextState(new UpSmashState());
					return;
				}
				else
				{
					if (controller->controlStickAngleBetween(50, 130))
					{
						player.setNextState(new UpTiltState());
						return;
					}
				}
			}
		}
		else if (controller->axisPercentageGreaterThan(Axis::Y, 66))
		{
			if (controller->controlStickAngleBetween(222, 318))
			{
				if (controller->cardinalDirectionChange(Axis::Y, 4))
				{
					player.setNextState(new DownSmashState());
					return;
				}
				else
				{
					if (controller->controlStickAngleBetween(230, 310))
					{
						player.setNextState(new DownTiltState());
						return;
					}
				}
			}
		}
		else if (controller->axisPercentageGreaterThan(Axis::X, 75))
		{
			if (controller->controlStickAngleBetween(0, 38) || controller->controlStickAngleBetween(322, 360))
			{
				if (player.getDirection() == Player::Direction::Left)
				{
					player.changeDirection();
				}
				player.setNextState(new ForwardSmashState());
				return;
			}
		}
		else if (controller->axisPercentageLessThan(Axis::X, -75))
		{
			if (controller->controlStickAngleBetween(142, 218))
			{
				if (player.getDirection() == Player::Direction::Right)
				{
					player.changeDirection();
				}
				player.setNextState(new ForwardSmashState());
				return;
			}
		}
		else if (controller->axisPercentageBetween(Axis::Y, -70, -20))
		{
			if (controller->controlStickAngleBetween(50, 130))
			{
				player.setNextState(new UpTiltState());
				return;
			}
		}
		else if (controller->axisPercentageBetween(Axis::Y, 20, 70))
		{
			if (controller->controlStickAngleBetween(230, 310))
			{
				player.setNextState(new DownTiltState());
				return;
			}
		}
		// if none of the above cases, try these
		if (controller->axisPercentageGreaterThan(Axis::X, 20) && player.getDirection() == Player::Direction::Right ||
			controller->axisPercentageLessThan(Axis::X, -20) && player.getDirection() == Player::Direction::Left)
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
	// X/Y presses
	else if (controller->buttonPressed(ButtonName::X) || controller->buttonPressed(ButtonName::Y))
	{
		player.setNextState(new JumpSquatState());
		return;
	}
	// Z presses
	else if (controller->buttonPressed(ButtonName::Z))
	{
		player.setNextState(new GrabState());
		return;
	}
	// D-Pad presses
	else if (controller->buttonPressed(ButtonName::D_PAD_UP))
	{
		player.setNextState(new TauntState());
		return;
	}
	// Control Stick presses
	else if (controller->axisPercentageLessThan(Axis::Y, -66))
	{
		if (controller->getControlStickAngle() > 42 && controller->getControlStickAngle() < 138)
		{
			if (controller->cardinalDirectionChange(Axis::Y, 4))
			{
				player.setNextState(new JumpSquatState());
				return;
			}
		}
	}
	else if (controller->axisPercentageGreaterThan(Axis::Y, 66))
	{
		if (controller->getControlStickAngle() > 222 && controller->getControlStickAngle() < 318)
		{
			player.setNextState(new SquatState());
			return;
		}
	}
	else if (controller->axisPercentageGreaterThan(Axis::X, 75))
	{
		if (controller->getControlStickAngle() >= 0 && controller->getControlStickAngle() < 38 || controller->getControlStickAngle() > 322 && controller->getControlStickAngle() < 360)
		{
			if (player.getDirection() == Player::Direction::Right)
			{
				player.setState(new DashState());
				return;
			}
		}
	}
	else if (controller->axisPercentageLessThan(Axis::X, -75))
	{
		if (controller->getControlStickAngle() > 142 && controller->getControlStickAngle() < 218)
		{
			if (player.getDirection() == Player::Direction::Left)
			{
				player.setState(new DashState());
				return;
			}
		}
	}
	// if none of the above cases, try this
	if (controller->axisPercentageGreaterThan(Axis::X, 0) && player.getDirection() == Player::Direction::Left ||
		controller->axisPercentageLessThan(Axis::X, 0) && player.getDirection() == Player::Direction::Right)
	{
		player.setNextState(new TurnState());
		return;
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
