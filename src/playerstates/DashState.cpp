#include "DashState.h"

#include <iostream>
#include "SFML/Graphics.hpp"
#include "../Player.h"
#include "../Controller.h"

#include "IdleState.h"
#include "RunState.h"
#include "DashAttackState.h"
#include "ForwardSmashState.h"
#include "ForwardSpecialState.h"
#include "TauntState.h"
#include "JumpSquatState.h"
#include "TurnState.h"

void DashState::init(Player& player)
{
	std::cout << "Entered dash state.\n";
	player.setOnScreenState("Dash");
}

void DashState::handleInput(Player& player, Controller* controller)
{
	if (controller == nullptr)
	{
		return;
	}

	// L/R presses
	if (controller->buttonPressed(controller->getControls()->L) || controller->buttonPressed(controller->getControls()->R))
	{
		// add analog shielding eventually
		if (controller->buttonPressed(controller->getControls()->A))
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
	// B presses
	else if (controller->buttonPressed(controller->getControls()->B))
	{
		if (controller->axisPercentageGreaterThan(Axis::X, 50))
		{
			if (controller->getControlStickAngle() >= 0 && controller->getControlStickAngle() < 54 || controller->getControlStickAngle() > 306 && controller->getControlStickAngle() < 360)
			{
				if (player.getDirection() == Player::Direction::Left)
				{
					player.changeDirection();
				}
				player.setNextState(new ForwardSpecialState());
				return;
			}
		}
		else if (controller->axisPercentageLessThan(Axis::X, -50))
		{
			if (controller->getControlStickAngle() > 126 && controller->getControlStickAngle() < 234)
			{
				if (player.getDirection() == Player::Direction::Right)
				{
					player.changeDirection();
				}
				player.setNextState(new ForwardSpecialState());
				return;
			}
		}
	}
	// A presses
	else if (controller->buttonPressed(controller->getControls()->A))
	{
		// TODO: only if last state was idle
		if (animFrame_< 4)
		{
			if (controller->axisPercentageGreaterThan(Axis::X, 75) && player.getDirection() == Player::Direction::Right ||
				controller->axisPercentageLessThan(Axis::X, -75) && player.getDirection() == Player::Direction::Left)
			{
				player.setNextState(new ForwardSmashState());
				return;
			}
		}
		else
		{
			player.setNextState(new DashAttackState());
			return;
		}
	}
	// X/Y presses
	else if (controller->buttonPressed(controller->getControls()->X) ||
		controller->buttonPressed(controller->getControls()->Y))
	{
		player.setNextState(new JumpSquatState());
		return;
	}
	// Z presses
	else if (controller->buttonPressed(controller->getControls()->Z))
	{
		std::cout << "dash grab\n";
		return;
	}
	// D-Pad presses
	else if (controller->buttonPressed(controller->getControls()->D_PAD_UP))
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
	else if (controller->axisPercentageLessThan(Axis::X, -20) && player.getDirection() == Player::Direction::Right ||
		controller->axisPercentageGreaterThan(Axis::X, 20) && player.getDirection() == Player::Direction::Left)
	{
		player.setNextState(new TurnState());
		return;
	}
	else if (controller->axisPercentageLessThan(Axis::X, 20) && controller->axisPercentageGreaterThan(Axis::X, -20))
	{
		player.setNextState(new IdleState());
		return;
	}
}

void DashState::update(Player& player, Controller* controller)
{
	// TODO: always get an initial dash regardless if control stick is pressed
	// if (animFrame_ == 1) provide boost of some kind? or maybe in init()?
	// or possibly change the MAX_HORIZONTAL_VELO or ACCEL based on state
	player.move();
	if (animFrame_ >= 11)
	{
		player.setNextState(new RunState());
	}
}

void DashState::animate(Player& player)
{
	if (animFrame_ == 1)
	{
		player.setAnimation("run_01");
	}
	else if (animFrame_ == 4)
	{
		player.setAnimation("run_02");
	}
	else if (animFrame_ == 7)
	{
		player.setAnimation("run_03");
	}
	else if (animFrame_ == 10)
	{
		player.setAnimation("run_04");
	}
	animFrame_++;
}

void DashState::destroy(Player& player)
{
	player.setOnScreenState("");
}