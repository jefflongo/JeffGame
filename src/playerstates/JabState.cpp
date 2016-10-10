#include "JabState.h"

#include <iostream>
#include "SFML/Graphics.hpp"
#include "../Globals.h"
#include "../Player.h"
#include "../Controller.h"

void JabState::init(Player& player)
{
	std::cout << "Entered jab state.\n";
	player.setOnScreenState("Jab");
}

void JabState::handleInput(Player& player, Controller* controller)
{
	if (controller == nullptr)
	{
		return;
	}

	if (animFrame_ >= 16)
	{
		IdleState::handleInput(player, controller);
	}
}

void JabState::update(Player& player, Controller* controller)
{
	player.decelOnGround();
	if (animFrame_ >= 17)
	{
		player.setNextState(new IdleState());
	}
}

void JabState::animate(Player& player)
{
	if (animFrame_ == 1)
	{
		player.setAnimation("jab_01");
	}
	else if (animFrame_ == 3)
	{
		player.setAnimation("jab_02");
	}
	else if (animFrame_ == 4)
	{
		player.setAnimation("jab_03");
	}
	else if (animFrame_ == 5)
	{
		player.setAnimation("jab_04");
	}
	else if (animFrame_ == 10)
	{
		player.setAnimation("jab_05");
	}
	animFrame_++;
}

void JabState::destroy(Player& player)
{
	player.setOnScreenState("");
}