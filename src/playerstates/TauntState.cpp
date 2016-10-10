#include "TauntState.h"

#include <iostream>
#include "SFML/Graphics.hpp"
#include "../Globals.h"
#include "../Player.h"
#include "../Controller.h"

#include "IdleState.h"

void TauntState::init(Player& player)
{
	std::cout << "Entered taunt state.\n";
	player.setOnScreenState("Taunt");
}

void TauntState::handleInput(Player& player, Controller* controller)
{
	if (controller == nullptr)
	{
		return;
	}
}

void TauntState::update(Player& player, Controller* controller)
{
	player.decelOnGround();
	if (animFrame_ >= 110)
	{
		player.setNextState(new IdleState());
	}
}

void TauntState::animate(Player& player)
{
	if (animFrame_ == 1)
	{
		player.setAnimation("taunt_01");
	}
	else if (animFrame_ == 10)
	{
		player.setAnimation("taunt_02");
	}
	else if (animFrame_ == 30)
	{
		player.setAnimation("taunt_03");
	}
	else if (animFrame_ == 40)
	{
		player.setAnimation("taunt_04");
	}
	else if (animFrame_ == 60)
	{
		player.setAnimation("taunt_05");
	}
	else if (animFrame_ == 70)
	{
		player.setAnimation("taunt_06");
	}
	else if (animFrame_ == 90)
	{
		player.setAnimation("taunt_07");
	}
	else if (animFrame_ == 95)
	{
		player.setAnimation("taunt_08");
	}
	else if (animFrame_ == 107)
	{
		player.setAnimation("taunt_09");
	}
	animFrame_++;
}

void TauntState::destroy(Player& player)
{
	player.setOnScreenState("");
}