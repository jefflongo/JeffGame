#include "GrabState.h"

#include <iostream>
#include "SFML/Graphics.hpp"
#include "../Globals.h"
#include "../Player.h"
#include "../Controller.h"

#include "IdleState.h"

void GrabState::init(Player& player)
{
	std::cout << "Entered grab state.\n";
	player.setOnScreenState("Grab");
}

void GrabState::handleInput(Player& player, Controller* controller)
{
	if (controller == nullptr)
	{
		return;
	}
}

void GrabState::update(Player& player, Controller* controller)
{
	player.decelOnGround();
	if (animFrame_ >= 30)
	{
		player.setNextState(new IdleState());
	}
}

void GrabState::animate(Player& player)
{
	if (animFrame_ == 1)
	{
		player.setAnimation("grab_01");
	}
	else if (animFrame_ == 7)
	{
		player.setAnimation("grab_02");
	}
	else if (animFrame_ == 8)
	{
		player.setAnimation("grab_03");
	}
	else if (animFrame_ == 20)
	{
		player.setAnimation("grab_04");
	}
	animFrame_++;
}

void GrabState::destroy(Player& player)
{
	player.setOnScreenState("");
}