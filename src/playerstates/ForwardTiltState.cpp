#include "ForwardTiltState.h"

#include <iostream>
#include "SFML/Graphics.hpp"
#include "../Player.h"
#include "../Controller.h"

#include "IdleState.h"

void ForwardTiltState::init(Player& player)
{
	std::cout << "Entered forward tilt state.\n";
	player.setOnScreenState("Forward Tilt");
}

void ForwardTiltState::handleInput(Player& player, Controller* controller)
{
	if (controller == nullptr) return;
}

void ForwardTiltState::update(Player& player, Controller* controller)
{
	player.decelOnGround();
	if (animFrame_ >= 26)
	{
		player.setNextState(new IdleState());
	}
}

void ForwardTiltState::animate(Player& player)
{
	if (animFrame_ == 1)
	{
		player.setAnimation("ftilt_01");
	}
	else if (animFrame_ == 5)
	{
		player.setAnimation("ftilt_02");
	}
	else if (animFrame_ == 6)
	{
		player.setAnimation("ftilt_03");
	}
	else if (animFrame_ == 17)
	{
		player.setAnimation("ftilt_04");
	}
	animFrame_++;
}

void ForwardTiltState::destroy(Player& player)
{
	player.setOnScreenState("");
}