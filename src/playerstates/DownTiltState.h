#ifndef DOWN_TILT_STATE_H_
#define DOWN_TILT_STATE_H_

#include "IdleState.h"

class Player;
class Controller;

class DownTiltState : public IdleState
{
public:
	void init(Player& player);
	void handleInput(Player& player, Controller* controller);
	void update(Player& player, Controller* controller);
	void animate(Player& player);
	void destroy(Player& player);
private:
};

#endif // DOWN_TILT_STATE_H_

