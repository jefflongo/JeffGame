#ifndef DASH_ATTACK_STATE_H_
#define DASH_ATTACK_STATE_H_

#include "IdleState.h"

class Player;
class Controller;

class DashAttackState : public IdleState
{
public:
	void init(Player& player);
	void handleInput(Player& player, Controller* controller);
	void update(Player& player, Controller* controller);
	void animate(Player& player);
	void destroy(Player& player);
private:
};

#endif // DASH_ATTACK_STATE_H_

