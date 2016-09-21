#include "ForwardSpecialState.h"

#include <iostream>
#include "SFML/Graphics.hpp"
#include "../Player.h"
#include "../Controller.h"

#include "IdleState.h"

void ForwardSpecialState::init(Player& player)
{
	std::cout << "Entered forward special state.\n";
	player.setOnScreenState("Forward Special");
}

void ForwardSpecialState::handleInput(Player& player, Controller* controller)
{
	if (controller == nullptr)
	{
		return;
	}
}

void ForwardSpecialState::update(Player& player, Controller* controller)
{
	if (animFrame_ >= 13 && animFrame_ <= 28)
	{
		if (player.getDirection() == Player::Direction::Right)
		{
			player.setPos(player.getPos().x + 15, player.getPos().y);
		}
		else
		{
			player.setPos(player.getPos().x - 15, player.getPos().y);
		}
	}
	else
	{
		player.decelOnGround();
	}
	if (animFrame_ >= 63)
	{
		player.setNextState(new IdleState());
	}
}

void ForwardSpecialState::animate(Player& player)
{
	if (animFrame_ == 1)
	{
		player.setAnimation("fspecial_01");
	}
	else if (animFrame_ == 4)
	{
		player.setAnimation("fspecial_02");
	}
	else if (animFrame_ == 6)
	{
		player.setAnimation("fspecial_03");
	}
	else if (animFrame_ == 13)
	{
		player.setAnimation("fspecial_04");
	}
	else if (animFrame_ == 20)
	{
		player.setAnimation("fspecial_05");
	}
	else if (animFrame_ == 21)
	{
		player.setAnimation("fspecial_06");
	}
	else if (animFrame_ == 22)
	{
		player.setAnimation("fspecial_07");
	}
	else if (animFrame_ == 23)
	{
		player.setAnimation("fspecial_08");
	}
	else if (animFrame_ == 26)
	{
		player.setAnimation("fspecial_09");
	}
	else if (animFrame_ == 28)
	{
		if (player.isOnGround())
		{
			player.setAnimation("fspecial_10");
		}
		else
		{
			player.setAnimation("fspecial_10air");
		}
	}
	animFrame_++;
}

void ForwardSpecialState::destroy(Player& player)
{
	player.setOnScreenState("");
}