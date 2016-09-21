#ifndef UNSQUAT_STATE_H_
#define UNSQUAT_STATE_H_

#include "../PlayerState.h"

class Player;
class Controller;

class UnsquatState : public PlayerState
{
public:
	void init(Player& player);
	void handleInput(Player& player, Controller* controller);
	void update(Player& player, Controller* controller);
	void animate(Player& player);
	void destroy(Player& player);
private:
};

#endif // UNSQUAT_STATE_H_