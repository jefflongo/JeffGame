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
	if (controller == nullptr) return;
	if (handleA(player, controller)) return;
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

bool JumpSquatState::handleA(Player& player, Controller* controller)
{
	if (controller->buttonPressed(ButtonName::A))
	{
		if (controller->getStickPosition(StickName::CONTROL_STICK).y <= -0.66)
		{
			if (controller->getFramesSinceDirectionChange(StickName::CONTROL_STICK).y <= 4)
			{
				player.setNextState(new UpSmashState());
				return true;
			}
		}
	}
	return false;
}