#include "JumpState.h"

#include <iostream>
#include "SFML/Graphics.hpp"
#include "../Player.h"
#include "../Controller.h"

#include "IdleState.h"

void JumpState::init(Player& player)
{
	std::cout << "Entered jump state.\n";
	player.setOnScreenState("Jump");
}

void JumpState::handleInput(Player& player, Controller* controller)
{
	if (controller == nullptr) return;
}

void JumpState::update(Player& player, Controller* controller)
{
	if (animFrame_ == 1)
	{
		player.jump();
	}
	else if (player.isOnGround())
	{
		player.setNextState(new IdleState());
		return;
	}
	else
	{
		player.move();
	}
}

void JumpState::animate(Player& player)
{
	if (animFrame_ == 1)
	{
		player.setAnimation("jump_01");
	}
	else if (animFrame_ == 8)
	{
		player.setAnimation("jump_02");
	}
	else if (animFrame_ == 10)
	{
		player.setAnimation("jump_03");
	}
	else if (animFrame_ == 12)
	{
		player.setAnimation("jump_04");
	}
	else if (animFrame_ == 13)
	{
		player.setAnimation("jump_05");
	}
	else if (animFrame_ == 15)
	{
		player.setAnimation("jump_06");
	}
	else if (animFrame_ == 20)
	{
		player.setAnimation("jump_07");
	}
	else if (animFrame_ == 22)
	{
		player.setAnimation("jump_08");
	}
	else if (animFrame_ == 26)
	{
		player.setAnimation("fall_01");
	}
	else if (animFrame_ == 30)
	{
		player.setAnimation("fall_02");
	}
	else if (animFrame_ == 34)
	{
		player.setAnimation("fall_03");
	}
	else if (animFrame_ == 38)
	{
		player.setAnimation("fall_04");
	}
	else if (animFrame_ >= 42)
	{
		animFrame_ = 25;
	}
	animFrame_++;
}

void JumpState::destroy(Player& player)
{
	player.setOnScreenState("");
}