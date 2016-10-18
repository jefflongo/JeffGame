#ifndef JUMPSQUAT_STATE_H_
#define JUMPSQUAT_STATE_H_

#include "../PlayerState.h"

class Player;
class Controller;

class JumpSquatState : public PlayerState
{
public:
	void init(Player& player);
	void handleInput(Player& player, Controller* controller);
	void update(Player& player, Controller* controller);
	void animate(Player& player);
	void destroy(Player& player);
private:
	bool handleA(Player& player, Controller* controller);
};

#endif // JUMPSQUAT_STATE_H_