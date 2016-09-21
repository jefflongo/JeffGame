#ifndef GAME_STATE_H_
#define GAME_STATE_H_

#include "SFML/Graphics.hpp"

class Game;

class GameState
{
public:
	virtual void init() = 0;
	virtual void update(Game& game) = 0;
	virtual void render(sf::RenderWindow& window) = 0;
	virtual void destroy() = 0;
};

#endif // GAME_STATE_H_

