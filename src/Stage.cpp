#include "Stage.h"

#include <iostream>
#include "Globals.h"

Stage::Stage()
{
	// add stage objects to their respective vectors
	sf::RectangleShape ground, platformLeft, platformCenter, platformRight;
	ground.setSize(sf::Vector2f(static_cast<float>(Globals::WINDOW_WIDTH) - 200, static_cast<float>(Globals::GROUND_OFFSET)));
	ground.setOrigin(0.5f*ground.getGlobalBounds().width, 0.5f*ground.getGlobalBounds().height);
	ground.setPosition(0.5f*Globals::WINDOW_WIDTH, Globals::WINDOW_HEIGHT - 0.5f*Globals::GROUND_OFFSET);
	ground.setFillColor(sf::Color::Green);
	collidableObjects_.push_back(ground);

	platformLeft.setSize(sf::Vector2f(200, static_cast<float>(Globals::GROUND_OFFSET)));
	platformLeft.setOrigin(0.5f*platformLeft.getGlobalBounds().width, 0.5f*platformLeft.getGlobalBounds().height);
	platformLeft.setPosition(0.5f*Globals::WINDOW_WIDTH - 200, Globals::WINDOW_HEIGHT - 0.5f*Globals::GROUND_OFFSET - 110);
	platformLeft.setFillColor(sf::Color::Green);
	permeableObjects_.push_back(platformLeft);

	platformCenter.setSize(sf::Vector2f(200, static_cast<float>(Globals::GROUND_OFFSET)));
	platformCenter.setOrigin(0.5f*platformCenter.getGlobalBounds().width, 0.5f*platformCenter.getGlobalBounds().height);
	platformCenter.setPosition(0.5f*Globals::WINDOW_WIDTH, Globals::WINDOW_HEIGHT - 0.5f*Globals::GROUND_OFFSET - 250);
	platformCenter.setFillColor(sf::Color::Green);
	permeableObjects_.push_back(platformCenter);

	platformRight.setSize(sf::Vector2f(200, static_cast<float>(Globals::GROUND_OFFSET)));
	platformRight.setOrigin(0.5f*platformRight.getGlobalBounds().width, 0.5f*platformRight.getGlobalBounds().height);
	platformRight.setPosition(0.5f*Globals::WINDOW_WIDTH + 200, Globals::WINDOW_HEIGHT - 0.5f*Globals::GROUND_OFFSET - 110);
	platformRight.setFillColor(sf::Color::Green);
	permeableObjects_.push_back(platformRight);

}

std::vector<sf::RectangleShape> Stage::getCollidableObjects() const
{
	return collidableObjects_;
}

std::vector<sf::RectangleShape> Stage::getPermeableObjects() const
{
	return permeableObjects_;
}

sf::RectangleShape Stage::getCollidableObject(unsigned int i) const
{
	if (i >= 0 && i < collidableObjects_.size())
	{
		return collidableObjects_[i];
	}
	else
	{
		std::cout << "ERROR: Invalid request for collidable stage object.\n";
		return collidableObjects_[0];
	}
}

sf::RectangleShape Stage::getPermeableObject(unsigned int i) const
{
	if (i >= 0 && i < permeableObjects_.size())
	{
		return permeableObjects_[i];
	}
	else
	{
		std::cout << "ERROR: Invalid request for permeable stage object.\n";
		return permeableObjects_[0];
	}
}

int Stage::groundCollision(const sf::RectangleShape& player, sf::Vector2f pos)
{
	sf::RectangleShape projectedPlayer;
	projectedPlayer.setSize(player.getSize());
	projectedPlayer.setPosition(pos);
	for (unsigned int i = 0; i < collidableObjects_.size(); i++)
	{
		if (projectedPlayer.getGlobalBounds().intersects(collidableObjects_[i].getGlobalBounds()))
		{
			return i;
		}
	}
	return -1;
}

int Stage::platformCollision(const sf::RectangleShape& player, sf::Vector2f pos)
{
	sf::RectangleShape projectedPlayer;
	projectedPlayer.setSize(player.getSize());
	projectedPlayer.setPosition(pos);
	for (unsigned int i = 0; i < permeableObjects_.size(); i++)
	{
		if (projectedPlayer.getGlobalBounds().intersects(permeableObjects_[i].getGlobalBounds()))
		{
			return i;
		}
	}
	return -1;
}

void Stage::render(sf::RenderWindow& window)
{
	for (unsigned int i = 0; i < collidableObjects_.size(); i++)
	{
		window.draw(collidableObjects_[i]);
	}
	for (unsigned int i = 0; i < permeableObjects_.size(); i++)
	{
		window.draw(permeableObjects_[i]);
	}
}