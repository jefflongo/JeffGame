#include "UpSmashState.h"

#include <iostream>
#include "SFML/Graphics.hpp"
#include "../Globals.h"
#include "../Player.h"
#include "../Controller.h"

#include "IdleState.h"

void UpSmashState::init(Player& player)
{
	std::cout << "Entered up smash state.\n";
	player.setOnScreenState("Up Smash");
}

void UpSmashState::handleInput(Player& player, Controller* controller)
{
	if (controller == nullptr)
	{
		return;
	}
}

void UpSmashState::update(Player& player, Controller* controller)
{
	player.decelOnGround();
	if (animFrame_ >= 41)
	{
		player.setNextState(new IdleState());
	}
}

void UpSmashState::animate(Player& player)
{
	if (animFrame_ == 1)
	{
		player.setAnimation("usmash_01");
	}
	else if (animFrame_ == 2)
	{
		player.setAnimation("usmash_02");
	}
	else if (animFrame_ == 9)
	{
		player.setAnimation("usmash_03");
	}
	else if (animFrame_ == 13)
	{
		player.setAnimation("usmash_04");
	}
	else if (animFrame_ == 14)
	{
		player.setAnimation("usmash_05");
	}
	else if (animFrame_ == 24)
	{
		player.setAnimation("usmash_06");
	}
	else if (animFrame_ == 27)
	{
		player.setAnimation("usmash_07");
	}
	else if (animFrame_ == 29)
	{
		player.setAnimation("usmash_08");
	}
	animFrame_++;
}

void UpSmashState::destroy(Player& player)
{
	player.setOnScreenState("");
}