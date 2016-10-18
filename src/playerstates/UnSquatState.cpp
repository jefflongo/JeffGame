#include "UnsquatState.h"

#include <iostream>
#include "SFML/Graphics.hpp"
#include "../Player.h"
#include "../Controller.h"

#include "IdleState.h"
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

void UnsquatState::init(Player& player)
{
	std::cout << "Entered unsquat state.\n";
	player.setOnScreenState("Unsquat");
}

void UnsquatState::handleInput(Player& player, Controller* controller)
{
	if (controller == nullptr) return;
	if (IdleState::handleB(player, controller)) return;
	if (IdleState::handleZ(player, controller)) return;
	if (IdleState::handleA(player, controller)) return;
	if (IdleState::handleCStick(player, controller)) return;
	if (IdleState::handleLR(player, controller)) return;
	if (IdleState::handleXY(player, controller)) return;
	if (IdleState::handleDPad(player, controller)) return;
	if (handleControlStick(player, controller)) return;
}

void UnsquatState::update(Player& player, Controller* controller)
{
	player.decelOnGround();
	if (animFrame_ >= 10)
	{
		player.setNextState(new IdleState());
	}
}

void UnsquatState::animate(Player& player)
{
	if (animFrame_ == 1)
	{
		player.setAnimation("crouch_04");
	}
	animFrame_++;
}

void UnsquatState::destroy(Player& player)
{
	player.setOnScreenState("");
}

bool UnsquatState::handleControlStick(Player& player, Controller* controller)
{
	if (controller->getStickPosition(StickName::CONTROL_STICK).y <= -0.66)
	{
		if (controller->getFramesSinceDirectionChange(StickName::CONTROL_STICK).y <= 4)
		{
			player.setNextState(new JumpSquatState());
			return true;
		}
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
		}
	}
	return false;
}