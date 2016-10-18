#ifndef RUN_STATE_H_
#define RUN_STATE_H_

#include "IdleState.h"

class Player;
class Controller;

class RunState : public IdleState
{
public:
	void init(Player& player);
	void handleInput(Player& player, Controller* controller);
	void update(Player& player, Controller* controller);
	void animate(Player& player);
	void destroy(Player& player);
private:
	bool handleA(Player& player, Controller* controller);
	bool handleB(Player& player, Controller* controller);
	bool handleZ(Player& player, Controller* controller);
	bool handleControlStick(Player& player, Controller* controller);
};

#endif // RUN_STATE_H_