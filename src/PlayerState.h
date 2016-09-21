#ifndef PLAYER_STATE_H_
#define PLAYER_STATE_H_

#include "SFML/Graphics.hpp"

class Player;
class Controller;

class PlayerState
{
public:
	typedef sf::Joystick::Axis Axis;
	virtual void init(Player& player) = 0;
	virtual void handleInput(Player& player, Controller* controller) = 0;
	virtual void update(Player& player, Controller* controller) = 0;
	virtual void animate(Player& player) = 0;
	virtual void destroy(Player& player) = 0;
protected:
	int animFrame_ = 1;
private:
};

#endif // PLAYER_STATE_H_