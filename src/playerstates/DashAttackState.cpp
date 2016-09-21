#include "DashAttackState.h"

#include <iostream>
#include "SFML/Graphics.hpp"
#include "../Player.h"
#include "../Controller.h"

void DashAttackState::init(Player& player)
{
	std::cout << "Entered dash attack state.\n";
	player.setOnScreenState("Dash Attack");
}

void DashAttackState::handleInput(Player& player, Controller* controller)
{
	if (controller == nullptr)
	{
		return;
	}

	// test
	if (animFrame_ >= 4 && animFrame_ <= 20)
	{
		if (player.getDirection() == Player::Direction::Right)
		{
			player.setPos(player.getPos().x + 10, player.getPos().y);
		}
		else
		{
			player.setPos(player.getPos().x - 10, player.getPos().y);
		}
	}
	else if (animFrame_ >= 23)
	{
		IdleState::handleInput(player, controller);
	}
}

void DashAttackState::update(Player& player, Controller* controller)
{
	player.decelOnGround();
	if (animFrame_ >= 39)
	{
		player.setNextState(new IdleState());
	}
}

void DashAttackState::animate(Player& player)
{
	if (animFrame_ == 1)
	{
		player.setAnimation("dashattack_01");
	}
	else if (animFrame_ == 4)
	{
		player.setAnimation("dashattack_02");
	}
	else if (animFrame_ == 8)
	{
		player.setAnimation("dashattack_03");
	}
	else if (animFrame_ == 12)
	{
		player.setAnimation("dashattack_04");
	}
	else if (animFrame_ == 16)
	{
		player.setAnimation("dashattack_05");
	}
	else if (animFrame_ == 20)
	{
		player.setAnimation("dashattack_06");
	}
	else if (animFrame_ == 23)
	{
		player.setAnimation("dashattack_07");
	}
	animFrame_++;
}

void DashAttackState::destroy(Player& player)
{
	player.setOnScreenState("");
}