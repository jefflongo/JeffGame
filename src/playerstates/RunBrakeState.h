#ifndef RUN_BRAKE_STATE_H_
#define RUN_BRAKE_STATE_H_

#include "IdleState.h"

class Player;
class Controller;

class RunBrakeState : public IdleState
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

#endif // RUN_BRAKE_STATE_H_