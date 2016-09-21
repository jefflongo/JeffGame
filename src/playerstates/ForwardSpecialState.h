#ifndef FORWARD_SPECIAL_STATE_H_
#define FORWARD_SPECIAL_STATE_H_

#include "../PlayerState.h"

class Player;
class Controller;

class ForwardSpecialState : public PlayerState
{
public:
	void init(Player& player);
	void handleInput(Player& player, Controller* controller);
	void update(Player& player, Controller* controller);
	void animate(Player& player);
	void destroy(Player& player);
private:
};

#endif // FORWARD_SPECIAL_STATE_H_