#include "TurnRunState.h"

#include <iostream>
#include "SFML/Graphics.hpp"
#include "../Globals.h"
#include "../Player.h"
#include "../Controller.h"

#include "IdleState.h"
#include "JumpSquatState.h"
#include "CrouchState.h"
#include "RunState.h"

void TurnRunState::init(Player& player)
{
	std::cout << "Entered turn run state.\n";
	player.setOnScreenState("Turn Run");
}

void TurnRunState::handleInput(Player& player, Controller* controller)
{
	if (controller == nullptr)
	{
		return;
	}

	// X/Y presses
	if (controller->buttonPressed(ButtonName::X) ||
		controller->buttonPressed(ButtonName::Y))
	{
		player.setNextState(new JumpSquatState());
		return;
	}
	// Control Stick presses
	else if (controller->axisPercentageLessThan(Axis::Y, -70))
	{
		if (controller->getControlStickAngle() > 42 && controller->getControlStickAngle() < 138)
		{
			player.setNextState(new JumpSquatState());
			return;
		}
	}
	// TODO: This number is lower than 30 if Run Brake is entered
	else if (controller->axisPercentageGreaterThan(Axis::Y, 20))
	{
		if (animFrame_ >= 30)
		{
			player.setNextState(new CrouchState());
			return;
		}
	}
	else if (controller->axisPercentageLessThan(Axis::X, -75) && player.getDirection() == Player::Direction::Left ||
		controller->axisPercentageGreaterThan(Axis::X, 75) && player.getDirection() == Player::Direction::Right)
	{
		if (animFrame_ >= 30)
		{
			player.setNextState(new RunState());
			return;
		}
	}
	else
	{
		if (animFrame_ >= 30)
		{
			player.setNextState(new IdleState());
			return;
		}
	}
}

void TurnRunState::update(Player& player, Controller* controller)
{
	player.decelOnGround();
	if (animFrame_ == 18)
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