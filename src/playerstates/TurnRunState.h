#ifndef TURN_RUN_STATE_H_
#define TURN_RUN_STATE_H_

#include "IdleState.h"

class Player;
class Controller;

class TurnRunState : public IdleState
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

#endif // TURN_RUN_STATE_H_