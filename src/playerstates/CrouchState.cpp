#include "CrouchState.h"

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
#include "GrabState.h"
#include "JumpSquatState.h"
#include "TauntState.h"
#include "DashState.h"
#include "TurnState.h"
#include "UnsquatState.h"

void CrouchState::init(Player& player)
{
	std::cout << "Entered crouch state.\n";
	player.setOnScreenState("Crouch");
}

void CrouchState::handleInput(Player& player, Controller* controller)
{
	// no side b, z does dtilt, and some delay to stand before any move <-- TODO: IMPLEMENT
	if (controller == nullptr) return;
	if (handleB(player, controller)) return;
	if (handleZ(player, controller)) return;
	if (IdleState::handleA(player, controller)) return;
	if (IdleState::handleCStick(player, controller)) return;
	if (IdleState::handleLR(player, controller)) return;
	if (IdleState::handleXY(player, controller)) return;
	if (IdleState::handleDPad(player, controller)) return;
	if (handleControlStick(player, controller)) return;
}

void CrouchState::update(Player& player, Controller* controller)
{
	player.decelOnGround();
}

void CrouchState::animate(Player& player)
{
	if (animFrame_ == 1)
	{
		player.setAnimation("crouch_02");
	}
	else if (animFrame_ == 10)
	{
		player.setAnimation("crouch_03");
	}
	else if (animFrame_ == 20)
	{
		player.setAnimation("crouch_04");
	}
	else if (animFrame_ == 30)
	{
		player.setAnimation("crouch_01");
	}
	else if (animFrame_ >= 40)
	{
		animFrame_ = 0;
	}
	animFrame_++;
}

void CrouchState::destroy(Player& player)
{
	player.setOnScreenState("");
}

bool CrouchState::handleB(Player& player, Controller* controller)
{
	if (controller->buttonPressed(ButtonName::B))
	{
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
	}
	return false;
}

bool CrouchState::handleZ(Player& player, Controller* controller)
{
	if (controller->buttonPressed(ButtonName::Z))
	{
		player.setNextState(new DownTiltState());
		return true;
	}
	return false;
}

bool CrouchState::handleControlStick(Player& player, Controller* controller)
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
	player.setNextState(new UnsquatState());
	return true;
}