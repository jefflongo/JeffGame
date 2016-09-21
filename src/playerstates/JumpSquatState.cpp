#include "JumpSquatState.h"

#include <iostream>
#include "SFML/Graphics.hpp"
#include "../Player.h"
#include "../Controller.h"

#include "JumpState.h"
#include "UpSmashState.h"
// #include "UpSpecialState.h"

void JumpSquatState::init(Player& player)
{
	std::cout << "Entered jumpsquat state.\n";
	player.setOnScreenState("Jumpsquat");
}

void JumpSquatState::handleInput(Player& player, Controller* controller)
{
	if (controller == nullptr)
	{
		return;
	}

	if (controller->buttonPressed(controller->getControls()->A))
	{
		if (controller->axisPercentageLessThan(Axis::Y, -70))
		{
			if (controller->getControlStickAngle() > 42 && controller->getControlStickAngle() < 138)
			{
				player.setNextState(new UpSmashState());
				return;
			}
		}
	}
}

void JumpSquatState::update(Player& player, Controller* controller)
{
	player.decelOnGround();
	if (animFrame_ >= 3)
	{
		player.setNextState(new JumpState());
	}
}

void JumpSquatState::animate(Player& player)
{
	if (animFrame_ == 1)
	{
		player.setAnimation("jumpsquat_01");
	}
	animFrame_++;
}

void JumpSquatState::destroy(Player& player)
{
	player.setOnScreenState("");
}