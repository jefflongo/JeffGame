#ifndef UP_TILT_STATE_H_
#define UP_TILT_STATE_H_

#include "IdleState.h"

class Player;
class Controller;

class UpTiltState : public IdleState
{
public:
	void init(Player& player);
	void handleInput(Player& player, Controller* controller);
	void update(Player& player, Controller* controller);
	void animate(Player& player);
	void destroy(Player& player);
private:
};

#endif // UP_TILT_STATE_H_