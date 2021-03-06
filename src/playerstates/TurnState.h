#ifndef TURN_STATE_H_
#define TURN_STATE_H_

#include "../PlayerState.h"

class Player;
class Controller;

class TurnState : public PlayerState
{
public:
	void init(Player& player);
	void handleInput(Player& player, Controller* controller);
	void update(Player& player, Controller* controller);
	void animate(Player& player);
	void destroy(Player& player);
private:
	bool handleControlStick(Player& player, Controller* controller);
};

#endif // TURN_STATE_H_