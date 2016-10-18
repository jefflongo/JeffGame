#include "DashState.h"

#include <iostream>
#include "SFML/Graphics.hpp"
#include "../Player.h"
#include "../Controller.h"

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
	// no neutral b, up b, or down b, z dash grab, only dash attack
	if (controller == nullptr) return;
	if (handleB(player, controller)) return;
	if (handleZ(player, controller)) return;
	if (handleA(player, controller)) return;
	if (IdleState::handleLR(player, controller)) return;
	if (IdleState::handleXY(player, controller)) return;
	if (IdleState::handleDPad(player, controller)) return;
	if (handleControlStick(player, controller)) return;
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

bool DashState::handleA(Player& player, Controller* controller)
{
	if (controller->buttonPressed(ButtonName::A))
	{
		if (controller->buttonPressed(ButtonName::L) || controller->buttonPressed(ButtonName::R))
		{
			std::cout << "dash grab\n";
			return true;
		}
		// TODO: only if last state was idle
		if (animFrame_ < 4)
		{
			if (controller->getStickPosition(StickName::CONTROL_STICK).x >= 0.80)
			{
				if (controller->getFramesSinceDirectionChange(StickName::CONTROL_STICK).x <= 4)
				{
					if (player.getDirection() == Player::Direction::Left)
					{
						player.changeDirection();
					}
					player.setNextState(new ForwardSmashState());
					return true;
				}
			}
			if (controller->getStickPosition(StickName::CONTROL_STICK).x <= -0.80)
			{
				if (controller->getFramesSinceDirectionChange(StickName::CONTROL_STICK).x <= 4)
				{
					if (player.getDirection() == Player::Direction::Right)
					{
						player.changeDirection();
					}
					player.setNextState(new ForwardSmashState());
					return true;
				}
			}
		}
		player.setNextState(new DashAttackState());
		return true;
	}
	return false;
}

bool DashState::handleB(Player& player, Controller* controller)
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

bool DashState::handleZ(Player& player, Controller* controller)
{
	if (controller->buttonPressed(ButtonName::Z))
	{
		std::cout << "dash grab\n";
		return true;
	}
	return false;
}

bool DashState::handleControlStick(Player& player, Controller* controller)
{
	if (controller->getStickPosition(StickName::CONTROL_STICK).y <= -0.66)
	{
		if (controller->getFramesSinceDirectionChange(StickName::CONTROL_STICK).y <= 4)
		{
			player.setNextState(new JumpSquatState());
			return true;
		}
	}
	if (controller->getStickPosition(StickName::CONTROL_STICK).x >= 0.25)
	{
		if (controller->getFramesSinceDirectionChange(StickName::CONTROL_STICK).x <= 4)
		{
			if (player.getDirection() == Player::Direction::Left)
			{
				// Smash Turn
				player.setNextState(new TurnState());
			}
		}
		return true;
	}
	if (controller->getStickPosition(StickName::CONTROL_STICK).x <= -0.25)
	{
		if (controller->getFramesSinceDirectionChange(StickName::CONTROL_STICK).x <= 4)
		{
			if (player.getDirection() == Player::Direction::Right)
			{
				// Smash Turn
				player.setNextState(new TurnState());
			}
		}
		return true;
	}
	player.setNextState(new IdleState());
	return true;
}