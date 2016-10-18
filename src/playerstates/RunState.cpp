#include "RunState.h"

#include <iostream>
#include "SFML/Graphics.hpp"
#include "../Player.h"
#include "../Controller.h"

#include "JumpSquatState.h"
#include "SquatState.h"
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
	if (controller == nullptr) return;
	if (handleB(player, controller)) return;
	if (handleZ(player, controller)) return;
	if (handleA(player, controller)) return;
	if (handleCStick(player, controller)) return;
	if (IdleState::handleLR(player, controller)) return;
	if (IdleState::handleXY(player, controller)) return;
	if (IdleState::handleDPad(player, controller)) return;
	if (handleControlStick(player, controller)) return;
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

bool RunState::handleA(Player& player, Controller* controller)
{
	if (controller->buttonPressed(ButtonName::A))
	{
		if (controller->buttonPressed(ButtonName::L) || controller->buttonPressed(ButtonName::R))
		{
			std::cout << "dash grab\n";
			return true;
		}
		player.setNextState(new DashAttackState());
		return true;
	}
	return false;
}

bool RunState::handleB(Player& player, Controller* controller)
{
	if (controller->buttonPressed(ButtonName::B))
	{
		if (controller->getStickPosition(StickName::CONTROL_STICK).x >= 0.60)
		{
			if (player.getDirection() == Player::Direction::Left)
			{
				player.changeDirection();
			}
			player.setNextState(new ForwardSpecialState());
			return true;
		}
		if (controller->getStickPosition(StickName::CONTROL_STICK).x <= -0.60)
		{
			if (player.getDirection() == Player::Direction::Right)
			{
				player.changeDirection();
			}
			player.setNextState(new ForwardSpecialState());
			return true;
		}
	}
	return false;
}

bool RunState::handleZ(Player& player, Controller* controller)
{
	if (controller->buttonPressed(ButtonName::Z))
	{
		std::cout << "dash grab\n";
		return true;
	}
	return false;
}

bool RunState::handleControlStick(Player& player, Controller* controller)
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
	if (controller->getStickPosition(StickName::CONTROL_STICK).x >= 0.25)
	{
		if (player.getDirection() == Player::Direction::Left)
		{
			player.setNextState(new RunBrakeState());
		}
		return true;
	}
	if (controller->getStickPosition(StickName::CONTROL_STICK).x <= -0.25)
	{
		if (player.getDirection() == Player::Direction::Right)
		{
			player.setNextState(new RunBrakeState());
		}
		return true;
	}
	if (controller->getStickPosition(StickName::CONTROL_STICK).x >= -0.25 &&
		controller->getStickPosition(StickName::CONTROL_STICK).x <= 0.25)
	{
		player.setNextState(new RunBrakeState());
		return true;
	}
	return false;
}