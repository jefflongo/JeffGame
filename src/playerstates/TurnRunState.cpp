#include "TurnRunState.h"

#include <iostream>
#include "SFML/Graphics.hpp"
#include "../Player.h"
#include "../Controller.h"

#include "JumpSquatState.h"
#include "SquatState.h"
#include "RunState.h"

void TurnRunState::init(Player& player)
{
	std::cout << "Entered turn run state.\n";
	player.setOnScreenState("Turn Run");
}

void TurnRunState::handleInput(Player& player, Controller* controller)
{
	if (controller == nullptr) return;
	if (IdleState::handleXY(player, controller)) return;
	if (handleControlStick(player, controller)) return;
}

void TurnRunState::update(Player& player, Controller* controller)
{
	player.decelOnGround();
	if (animFrame_ >= 30)
	{
		player.setNextState(new IdleState());
	}
	else if (animFrame_ == 18)
	{
		player.changeDirection();
	}
}

void TurnRunState::animate(Player& player)
{
	if (animFrame_ == 1)
	{
		player.setAnimation("run_09");
	}
	else if (animFrame_ == 9)
	{
		player.setAnimation("run_08");
	}
	else if (animFrame_ == 18)
	{
		player.setAnimation("run_06");
	}
	animFrame_++;
}

void TurnRunState::destroy(Player& player)
{
	player.setOnScreenState("");
}

bool TurnRunState::handleControlStick(Player& player, Controller* controller)
{
	if (controller->getStickPosition(StickName::CONTROL_STICK).y <= -0.66)
	{
		if (controller->getFramesSinceDirectionChange(StickName::CONTROL_STICK).y <= 4)
		{
			player.setNextState(new JumpSquatState());
			return true;
		}
	}
	// TODO: This number is lower than 30 if Run Brake is entered
	if (controller->getStickPosition(StickName::CONTROL_STICK).y >= 0.70)
	{
		player.setNextState(new SquatState());
		return true;
	}
	if (controller->getStickPosition(StickName::CONTROL_STICK).x <= -0.80 &&
		player.getDirection() == Player::Direction::Left ||
		controller->getStickPosition(StickName::CONTROL_STICK).x >= 0.80 && 
		player.getDirection() == Player::Direction::Right)
	{
		if (animFrame_ >= 30)
		{
			player.setNextState(new RunState());
			return true;
		}
	}
	return false;
}