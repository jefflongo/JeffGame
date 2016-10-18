#include "IdleState.h"

#include <iostream>
#include "SFML/Graphics.hpp"
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
	if (controller == nullptr) return;
	// Hierarchy of button press priority: START > B > Z > A > C_STICK > L/R > X/Y > D_PAD
	if (handleB(player, controller)) return;
	if (handleZ(player, controller)) return;
	if (handleA(player, controller)) return;
	if (handleCStick(player, controller)) return;
	if (handleLR(player, controller)) return;
	if (handleXY(player, controller)) return;
	if (handleDPad(player, controller)) return;
	if (handleControlStick(player, controller)) return;
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

bool IdleState::handleA(Player& player, Controller* controller)
{
	if (controller->buttonPressed(ButtonName::A))
	{
		if (controller->buttonPressed(ButtonName::L) || controller->buttonPressed(ButtonName::R))
		{
			player.setNextState(new GrabState());
			return true;
		}
		if (controller->getStickPosition(StickName::CONTROL_STICK).x >= 0.80)
		{
			if (controller->getFramesSinceDirectionChange(StickName::CONTROL_STICK).x <= 4)
			{
				if (player.getDirection() == Player::Direction::Left)
				{
					player.changeDirection();
				}
				player.setNextState(new ForwardSmashState());
				return true;
			}
		}
		if (controller->getStickPosition(StickName::CONTROL_STICK).x <= -0.80)
		{
			if (controller->getFramesSinceDirectionChange(StickName::CONTROL_STICK).x <= 4)
			{
				if (player.getDirection() == Player::Direction::Right)
				{
					player.changeDirection();
				}
				player.setNextState(new ForwardSmashState());
				return true;
			}
		}
		if (controller->getStickPosition(StickName::CONTROL_STICK).y <= -0.66)
		{
			if (controller->getFramesSinceDirectionChange(StickName::CONTROL_STICK).y <= 4)
			{
				player.setNextState(new UpSmashState());
				return true;
			}
		}
		if (controller->getStickPosition(StickName::CONTROL_STICK).y >= 0.66)
		{
			if (controller->getFramesSinceDirectionChange(StickName::CONTROL_STICK).y <= 4)
			{
				player.setNextState(new DownSmashState());
				return true;
			}
		}
		if (controller->getStickPosition(StickName::CONTROL_STICK).x >= 0.25)
		{
			if (controller->getStickAngle(StickName::CONTROL_STICK) >= 0 &&
				controller->getStickAngle(StickName::CONTROL_STICK) <= 50 ||
				controller->getStickAngle(StickName::CONTROL_STICK) >= 310 &&
				controller->getStickAngle(StickName::CONTROL_STICK) <= 360)
			{
				if (player.getDirection() == Player::Direction::Right)
				{
					player.setNextState(new ForwardTiltState());
					return true;
				}
				else
				{
					player.setNextState(new JabState());
					return true;
				}
			}
		}
		if (controller->getStickPosition(StickName::CONTROL_STICK).x <= -0.25)
		{
			if (controller->getStickAngle(StickName::CONTROL_STICK) >= 130 &&
				controller->getStickAngle(StickName::CONTROL_STICK) <= 230)
			{
				if (player.getDirection() == Player::Direction::Left)
				{
					player.setNextState(new ForwardTiltState());
					return true;
				}
				else
				{
					player.setNextState(new JabState());
					return true;
				}
			}
		}
		if (controller->getStickPosition(StickName::CONTROL_STICK).y <= -0.25)
		{
			player.setNextState(new UpTiltState());
			return true;
		}
		if (controller->getStickPosition(StickName::CONTROL_STICK).y >= 0.25)
		{
			player.setNextState(new DownTiltState());
			return true;
		}
		player.setNextState(new JabState());
		return true;
	}
	return false;
}

bool IdleState::handleB(Player& player, Controller* controller)
{
	if (controller->buttonPressed(ButtonName::B))
	{
		if (controller->getStickPosition(StickName::CONTROL_STICK).x >= 0.60)
		{
			if (player.getDirection() == Player::Direction::Left)
			{
				player.changeDirection();
			}
			player.setNextState(new ForwardSpecialState());
			return true;
		}
		if (controller->getStickPosition(StickName::CONTROL_STICK).x <= -0.60)
		{
			if (player.getDirection() == Player::Direction::Right)
			{
				player.changeDirection();
			}
			player.setNextState(new ForwardSpecialState());
			return true;
		}
		if (controller->getStickPosition(StickName::CONTROL_STICK).y <= -0.55)
		{
			std::cout << "up b\n";
			return true;
		}
		if (controller->getStickPosition(StickName::CONTROL_STICK).y >= 0.55)
		{
			std::cout << "down b\n";
			return true;
		}
		std::cout << "neutral b\n";
		return true;
	}
	return false;
}

bool IdleState::handleXY(Player& player, Controller* controller)
{
	if (controller->buttonPressed(ButtonName::X) || controller->buttonPressed(ButtonName::Y))
	{
		player.setNextState(new JumpSquatState());
		return true;
	}
	return false;
}

bool IdleState::handleZ(Player& player, Controller* controller)
{
	if (controller->buttonPressed(ButtonName::Z))
	{
		player.setNextState(new GrabState());
		return true;
	}
	return false;
}

bool IdleState::handleLR(Player& player, Controller* controller)
{
	if (controller->buttonPressed(ButtonName::L) || controller->buttonPressed(ButtonName::R))
	{
		// TODO: Add analog shielding eventually
		std::cout << "shield\n";
		return true;
	}
	return false;
}

bool IdleState::handleDPad(Player& player, Controller* controller)
{
	if (controller->buttonPressed(ButtonName::D_PAD_UP))
	{
		player.setNextState(new TauntState());
		return true;
	}
	return false;
}

bool IdleState::handleCStick(Player& player, Controller* controller)
{
	return false;
}

bool IdleState::handleControlStick(Player& player, Controller* controller)
{
	if (controller->getStickPosition(StickName::CONTROL_STICK).y <= -0.66)
	{
		if (controller->getFramesSinceDirectionChange(StickName::CONTROL_STICK).y <= 4)
		{
			player.setNextState(new JumpSquatState());
			return true;
		}
	}
	if (controller->getStickPosition(StickName::CONTROL_STICK).y >= 0.70)
	{
		player.setNextState(new SquatState());
		return true;
	}
	if (controller->getStickPosition(StickName::CONTROL_STICK).x >= 0.80)
	{
		if (controller->getFramesSinceDirectionChange(StickName::CONTROL_STICK).x <= 4)
		{
			if (player.getDirection() == Player::Direction::Right)
			{
				player.setNextState(new DashState());
				return true;
			}
			else
			{
				// Smash Turn
				player.setNextState(new TurnState());
				return true;
			}
		}
	}
	if (controller->getStickPosition(StickName::CONTROL_STICK).x <= -0.80)
	{
		if (controller->getFramesSinceDirectionChange(StickName::CONTROL_STICK).x <= 4)
		{
			if (player.getDirection() == Player::Direction::Left)
			{
				player.setNextState(new DashState());
				return true;
			}
			else
			{
				// Smash Turn
				player.setNextState(new TurnState());
				return true;
			}
		}
	}
	if (controller->getStickPosition(StickName::CONTROL_STICK).x >= 0.25)
	{
		if (player.getDirection() == Player::Direction::Right)
		{
			std::cout << "walk.\n";
			return true;
		}
		else
		{
			// Smash Turn
			player.setNextState(new TurnState());
			return true;
		}
	}
	if (controller->getStickPosition(StickName::CONTROL_STICK).x <= -0.25)
	{
		if (player.getDirection() == Player::Direction::Left)
		{
			std::cout << "walk.\n";
			return true;
		}
		else
		{
			// Smash Turn
			player.setNextState(new TurnState());
			return true;
		}
	}
	return false;
}