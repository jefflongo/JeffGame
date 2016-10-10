#include "RunState.h"

#include <iostream>
#include "SFML/Graphics.hpp"
#include "../Globals.h"
#include "../Player.h"
#include "../Controller.h"

#include "IdleState.h"
#include "JumpSquatState.h"
#include "RunBrakeState.h"
#include "DashAttackState.h"
// #include "UpSpecialState.h"
#include "ForwardSpecialState.h"
// #include "DownSpecialState.h"
#include "TauntState.h"

void RunState::init(Player& player)
{
	std::cout << "Entered run state.\n";
	player.setOnScreenState("Run");
}

void RunState::handleInput(Player& player, Controller* controller)
{
	if (controller == nullptr)
	{
		return;
	}

	// L/R presses
	if (controller->buttonPressed(ButtonName::L) || controller->buttonPressed(ButtonName::R))
	{
		// add analog shielding eventually
		if (controller->buttonPressed(ButtonName::A))
		{
			//player.setNextState(new DashGrabState());
			return;
		}
		else if (controller->axisPercentageGreaterThan(Axis::Y, 70))
		{
			std::cout << "spotdodge\n";
			return;
		}
		else
		{
			std::cout << "shield\n";
			return;
		}
	}
	// A presses
	else if (controller->buttonPressed(ButtonName::A))
	{
		player.setNextState(new DashAttackState());
		return;
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
		std::cout << "Run grab\n";
		return;
	}
	// D-Pad presses
	else if (controller->buttonPressed(ButtonName::D_PAD_UP))
	{
		player.setNextState(new TauntState());
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
	else if (controller->axisPercentageLessThan(Axis::X, 20) && player.getDirection() == Player::Direction::Right ||
		controller->axisPercentageGreaterThan(Axis::X, -20) && player.getDirection() == Player::Direction::Left)
	{
		player.setNextState(new RunBrakeState());
		return;
	}
}

void RunState::update(Player& player, Controller* controller)
{
	player.move();
}

void RunState::animate(Player& player)
{
	if (animFrame_ == 1)
	{
		player.setAnimation("run_04");
	}
	else if (animFrame_ == 3)
	{
		player.setAnimation("run_04");
	}
	else if (animFrame_ == 6)
	{
		player.setAnimation("run_05");
	}
	else if (animFrame_ == 9)
	{
		player.setAnimation("run_06");
	}
	else if (animFrame_ == 12)
	{
		player.setAnimation("run_07");
	}
	else if (animFrame_ == 15)
	{
		player.setAnimation("run_08");
	}
	else if (animFrame_ == 18)
	{
		player.setAnimation("run_09");
	}
	else if (animFrame_ == 21)
	{
		player.setAnimation("run_10");
	}
	else if (animFrame_ >= 24)
	{
		animFrame_ = 0;
	}
	animFrame_++;
}

void RunState::destroy(Player& player)
{
	player.setOnScreenState("");
}