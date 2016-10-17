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
protected:
	virtual bool handleA(Player& player, Controller* controller);
	virtual bool handleB(Player& player, Controller* controller);
	virtual bool handleXY(Player& player, Controller* controller);
	virtual bool handleZ(Player& player, Controller* controller);
	virtual bool handleLR(Player& player, Controller* controller);
	virtual bool handleDPad(Player& player, Controller* controller);
	virtual bool handleCStick(Player& player, Controller* controller);
	virtual bool handleControlStick(Player& player, Controller* controller);
private:
};

#endif // IDLE_STATE_H_