#include "ForwardSmashState.h"

#include <iostream>
#include "SFML/Graphics.hpp"
#include "../Player.h"
#include "../Controller.h"

#include "IdleState.h"

void ForwardSmashState::init(Player& player)
{
	std::cout << "Entered forward smash state.\n";
	player.setOnScreenState("Forward Smash");
}

void ForwardSmashState::handleInput(Player& player, Controller* controller)
{
	if (controller == nullptr)
	{
		return;
	}
}

void ForwardSmashState::update(Player& player, Controller* controller)
{
	player.decelOnGround();
	// test
	if (animFrame_ >= 9 && animFrame_ <= 34)
	{
		if (player.getDirection() == Player::Direction::Right)
		{
			player.setPos(player.getPos().x + 3, player.getPos().y);
		}
		else
		{
			player.setPos(player.getPos().x - 3, player.getPos().y);
		}
	}
	else if (animFrame_ >= 39)
	{
		player.setNextState(new IdleState());
	}
}

void ForwardSmashState::animate(Player& player)
{
	if (animFrame_ == 1)
	{
		player.setAnimation("fsmash_01");
	}
	else if (animFrame_ == 9)
	{
		player.setAnimation("fsmash_02");
	}
	else if (animFrame_ == 13)
	{
		player.setAnimation("fsmash_03");
	}
	else if (animFrame_ == 16)
	{
		player.setAnimation("fsmash_04");
	}
	else if (animFrame_ == 22)
	{
		player.setAnimation("fsmash_05");
	}
	else if (animFrame_ == 34)
	{
		player.setAnimation("fsmash_06");
	}
	else if (animFrame_ == 38)
	{
		player.setAnimation("fsmash_07");
	}
	animFrame_++;
}

void ForwardSmashState::destroy(Player& player)
{
	player.setOnScreenState("");
}