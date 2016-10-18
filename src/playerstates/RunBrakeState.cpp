#include "RunBrakeState.h"

#include <iostream>
#include "SFML/Graphics.hpp"
#include "../Player.h"
#include "../Controller.h"

#include "IdleState.h"
#include "JumpSquatState.h"
#include "SquatState.h"
#include "TurnRunState.h"

void RunBrakeState::init(Player& player)
{
	std::cout << "Entered run brake state.\n";
	player.setOnScreenState("Run Brake");
}

void RunBrakeState::handleInput(Player& player, Controller* controller)
{
	if (controller == nullptr) return;
	if (IdleState::handleXY(player, controller)) return;
	if (handleControlStick(player, controller)) return;
}

void RunBrakeState::update(Player& player, Controller* controller)
{
	player.decelOnGround();
	if (animFrame_ >= 18)
	{
		player.setNextState(new IdleState());
	}
}

void RunBrakeState::animate(Player& player)
{
	player.setAnimation("run_09");
	animFrame_++;
}

void RunBrakeState::destroy(Player& player)
{
	player.setOnScreenState("");
}

bool RunBrakeState::handleControlStick(Player& player, Controller* controller)
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
	if (controller->getStickPosition(StickName::CONTROL_STICK).x <= -0.25 &&
		player.getDirection() == Player::Direction::Right ||
		controller->getStickPosition(StickName::CONTROL_STICK).x >= 0.25 && 
		player.getDirection() == Player::Direction::Left)
	{
		player.setNextState(new TurnRunState());
		return true;
	}
	return false;
}