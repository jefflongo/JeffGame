#include "Battle.h"

#include <iostream>
#include "../Game.h"
#include "../Controller.h"
#include "../playerstates/IdleState.h"

Battle::Battle(Controller* controller) : player_(controller, Player::Direction::Right, 200)
{

}

void Battle::init()
{
	std::cout << "Battle initialized.\n";
	player_.setState(new IdleState());
}

void Battle::update(Game& game)
{
	debugMode_ = game.getDebugState();
	player_.update(stage_);
}

void Battle::render(sf::RenderWindow& window)
{
	stage_.render(window);
	player_.render(window, debugMode_);
}

void Battle::destroy()
{

}