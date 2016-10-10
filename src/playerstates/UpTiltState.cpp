#include "UpTiltState.h"

#include <iostream>
#include "SFML/Graphics.hpp"
#include "../Globals.h"
#include "../Player.h"
#include "../Controller.h"

void UpTiltState::init(Player& player)
{
	std::cout << "Entered up tilt state.\n";
	player.setOnScreenState("Up Tilt");
}

void UpTiltState::handleInput(Player& player, Controller* controller)
{
	if (controller == nullptr)
	{
		return;
	}

	if (animFrame_ >= 23)
	{
		IdleState::handleInput(player, controller);
	}
}

void UpTiltState::update(Player& player, Controller* controller)
{
	player.decelOnGround();
	if (animFrame_ >= 23)
	{
		player.setNextState(new IdleState());
	}
}

void UpTiltState::animate(Player& player)
{
	if (animFrame_ == 1)
	{
		player.setAnimation("utilt_01");
	}
	else if (animFrame_ == 6)
	{
		player.setAnimation("utilt_02");
	}
	else if (animFrame_ == 7)
	{
		player.setAnimation("utilt_03");
	}
	else if (animFrame_ == 8)
	{
		player.setAnimation("utilt_04");
	}
	else if (animFrame_ == 15)
	{
		player.setAnimation("utilt_05");
	}
	else if (animFrame_ == 17)
	{
		player.setAnimation("utilt_06");
	}
	else if (animFrame_ == 20)
	{
		player.setAnimation("utilt_07");
	}
	animFrame_++;
}

void UpTiltState::destroy(Player& player)
{
	player.setOnScreenState("");
}