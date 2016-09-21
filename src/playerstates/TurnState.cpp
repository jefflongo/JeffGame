#include "TurnState.h"

#include <iostream>
#include "SFML/Graphics.hpp"
#include "../Player.h"
#include "../Controller.h"

#include "IdleState.h"
#include "DashState.h"

void TurnState::init(Player& player)
{
	std::cout << "Entered turn state.\n";
	player.setOnScreenState("Turn");
}

void TurnState::handleInput(Player& player, Controller* controller)
{
	if (controller == nullptr)
	{
		return;
	}

	if (controller->axisPercentageGreaterThan(Axis::X, 75) && player.getDirection() == Player::Direction::Right ||
		controller->axisPercentageLessThan(Axis::X, -75) && player.getDirection() == Player::Direction::Left)
	{
		player.setNextState(new DashState());
		return;
	}
	else
	{
		player.setNextState(new IdleState());
		return;
	}
}

void TurnState::update(Player& player, Controller* controller)
{
	player.changeDirection();
	player.decelOnGround();
}

void TurnState::animate(Player& player)
{
	player.setAnimation("idle_01");
	animFrame_++;
}

void TurnState::destroy(Player& player)
{
	player.setOnScreenState("");
}