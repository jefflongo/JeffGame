#include "RunBrakeState.h"

#include <iostream>
#include "SFML/Graphics.hpp"
#include "../Player.h"
#include "../Controller.h"

#include "IdleState.h"
#include "JumpSquatState.h"
#include "CrouchState.h"
#include "TurnRunState.h"

void RunBrakeState::init(Player& player)
{
	std::cout << "Entered run brake state.\n";
	player.setOnScreenState("Run Brake");
}

void RunBrakeState::handleInput(Player& player, Controller* controller)
{
	if (controller == nullptr)
	{
		return;
	}

	// X/Y presses
	if (controller->buttonPressed(controller->getControls()->X) ||
		controller->buttonPressed(controller->getControls()->Y))
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
	else if (controller->axisPercentageGreaterThan(Axis::Y, 20))
	{
		player.setNextState(new CrouchState());
		return;
	}
	else if (controller->axisPercentageLessThan(Axis::X, -20) && player.getDirection() == Player::Direction::Right ||
		controller->axisPercentageGreaterThan(Axis::X, 20) && player.getDirection() == Player::Direction::Left)
	{
		player.setNextState(new TurnRunState());
		return;
	}
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