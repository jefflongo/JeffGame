#ifndef CROUCH_STATE_H_
#define CROUCH_STATE_H_

#include "IdleState.h"

class Player;
class Controller;

class CrouchState : public IdleState
{
public:
	void init(Player& player);
	void handleInput(Player& player, Controller* controller);
	void update(Player& player, Controller* controller);
	void animate(Player& player);
	void destroy(Player& player);
private:
	bool handleB(Player& player, Controller* controller);
	bool handleZ(Player& player, Controller* controller);
	bool handleControlStick(Player& player, Controller* controller);
};

#endif // CROUCH_STATE_H_