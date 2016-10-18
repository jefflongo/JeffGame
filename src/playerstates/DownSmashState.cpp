#include "DownSmashState.h"

#include <iostream>
#include "SFML/Graphics.hpp"
#include "../Player.h"
#include "../Controller.h"

void DownSmashState::init(Player& player)
{
	std::cout << "Entered down smash state.\n";
	player.setOnScreenState("Down Smash");
}

void DownSmashState::handleInput(Player& player, Controller* controller)
{
	if (controller == nullptr) return;
	if (animFrame_ >= 46 && animFrame_ < 49)
	{
		IdleState::handleInput(player, controller);
	}
}

void DownSmashState::update(Player& player, Controller* controller)
{
	player.decelOnGround();
	if (animFrame_ >= 49)
	{
		player.setNextState(new IdleState());
	}
}

void DownSmashState::animate(Player& player)
{
	if (animFrame_ == 1)
	{
		player.setAnimation("dsmash_01");
	}
	else if (animFrame_ == 4)
	{
		player.setAnimation("dsmash_02");
	}
	else if (animFrame_ == 6)
	{
		player.setAnimation("dsmash_03");
	}
	else if (animFrame_ == 8)
	{
		player.setAnimation("dsmash_04");
	}
	else if (animFrame_ == 10)
	{
		player.setAnimation("dsmash_05");
	}
	else if (animFrame_ == 20)
	{
		player.setAnimation("dsmash_06");
	}
	else if (animFrame_ == 25)
	{
		player.setAnimation("dsmash_07");
	}
	else if (animFrame_ == 42)
	{
		player.setAnimation("dsmash_08");
	}
	animFrame_++;
}

void DownSmashState::destroy(Player& player)
{
	player.setOnScreenState("");
}