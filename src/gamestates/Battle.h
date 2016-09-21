#ifndef BATTLE_H_
#define BATTLE_H_

#include "SFML/Graphics.hpp"
#include "SFML/Audio.hpp"
#include "../GameState.h"
#include "../Stage.h"
#include "../Player.h"

class Game;
class Controller;

class Battle : public GameState
{
public:
	Battle(){}
	Battle(Controller* controller);
	void init();
	void update(Game& game);
	void render(sf::RenderWindow& window);
	void destroy();
private:
	Stage stage_;
	Player player_;
	bool debugMode_ = false;
};

#endif // BATTLE_H_