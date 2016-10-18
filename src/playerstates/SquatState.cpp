#include "SquatState.h"

#include <iostream>
#include "SFML/Graphics.hpp"
#include "../Player.h"
#include "../Controller.h"

#include "ForwardSpecialState.h"
#include "JabState.h"
#include "UpSmashState.h"
#include "DownSmashState.h"
#include "ForwardSmashState.h"
#include "UpTiltState.h"
#include "DownTiltState.h"
#include "ForwardTiltState.h"
#include "JumpSquatState.h"
#include "GrabState.h"
#include "TauntState.h"
#include "CrouchState.h"
#include "UnsquatState.h"

void SquatState::init(Player& player)
{
	std::cout << "Entered squat state.\n";
	player.setOnScreenState("Squat");
}

void SquatState::handleInput(Player& player, Controller* controller)
{
	if (controller == nullptr) return;
	if (IdleState::handleB(player, controller)) return;
	if (IdleState::handleZ(player, controller)) return;
	if (IdleState::handleA(player, controller)) return;
	if (IdleState::handleCStick(player, controller)) return;
	if (IdleState::handleLR(player, controller)) return;
	if (IdleState::handleXY(player, controller)) return;
	if (IdleState::handleDPad(player, controller)) return;
	if (handleControlStick(player, controller)) return;
}

void SquatState::update(Player& player, Controller* controller)
{
	player.decelOnGround();
}

void SquatState::animate(Player& player)
{
	if (animFrame_ == 1)
	{
		player.setAnimation("crouch_01");
	}
	animFrame_++;
}

void SquatState::destroy(Player& player)
{
	player.setOnScreenState("");
}

bool SquatState::handleControlStick(Player& player, Controller* controller)
{
	if (controller->getStickPosition(StickName::CONTROL_STICK).y <= -0.66)
	{
		if (controller->getFramesSinceDirectionChange(StickName::CONTROL_STICK).y <= 4)
		{
			player.setNextState(new JumpSquatState());
			return true;
		}
	}
	if (controller->getStickPosition(StickName::CONTROL_STICK).y >= 0.66)
	{
		if (animFrame_ == 7)
		{
			player.setNextState(new CrouchState());
		}
		return true;
	}
	player.setNextState(new UnsquatState());
	return true;
}