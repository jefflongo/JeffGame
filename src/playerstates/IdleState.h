#ifndef IDLE_STATE_H_
#define IDLE_STATE_H_

#include "../PlayerState.h"

class Player;
class Controller;

class IdleState : public PlayerState
{
public:
	virtual void init(Player& player);
	virtual void handleInput(Player& player, Controller* controller);
	virtual void update(Player& player, Controller* controller);
	virtual void animate(Player& player);
	virtual void destroy(Player& player);
private:
};

#endif // IDLE_STATE_H_