#include "DownTiltState.h"

#include <iostream>
#include "SFML/Graphics.hpp"
#include "../Player.h"
#include "../Controller.h"

#include "CrouchState.h"

void DownTiltState::init(Player& player)
{
	std::cout << "Entered down tilt state.\n";
	player.setOnScreenState("Down Tilt");
}

void DownTiltState::handleInput(Player& player, Controller* controller)
{
	if (controller == nullptr) return;
	if (animFrame_ >= 28 && animFrame_ < 29)
	{
		IdleState::handleInput(player, controller);
	}
}

void DownTiltState::update(Player& player, Controller* controller)
{
	player.decelOnGround();
	if (animFrame_ >= 29)
	{
		if (handleControlStick(player, controller)) return;
	}
}

void DownTiltState::animate(Player& player)
{
	if (animFrame_ == 1)
	{
		player.setAnimation("dtilt_01");
	}
	else if (animFrame_ == 7)
	{
		player.setAnimation("dtilt_02");
	}
	else if (animFrame_ == 8)
	{
		player.setAnimation("dtilt_03");
	}
	else if (animFrame_ == 10)
	{
		player.setAnimation("dtilt_04");
	}
	else if (animFrame_ == 20)
	{
		player.setAnimation("dtilt_05");
	}
	animFrame_++;
}

void DownTiltState::destroy(Player& player)
{
	player.setOnScreenState("");
}

bool DownTiltState::handleControlStick(Player& player, Controller* controller)
{
	if (controller->getStickPosition(StickName::CONTROL_STICK).y > 0.25)
	{
		player.setNextState(new CrouchState());
		return true;
	}
	player.setNextState(new IdleState());
	return true;
}