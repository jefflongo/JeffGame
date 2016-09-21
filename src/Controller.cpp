#include "Controller.h"

Controller::Controller(){}

Controller::Controller(unsigned int controllerId, Controls controls)
{
	controllerId_ = controllerId;
	controls_ = controls;
}

void Controller::update()
{
	checkHeldButtons();
	checkStickDirection();
}

Controls* Controller::getControls()
{
	return &controls_;
}

Controller::CardinalDirections Controller::getStickDirection() const
{
	return stickDirection_;
}

int Controller::getFramesSinceStickDirectionChange() const
{
	return framesSinceStickDirectionChange_;
}

float Controller::getAxisPosition(sf::Joystick::Axis axis) const
{
	float deadzone, pos = sf::Joystick::getAxisPosition(controllerId_, axis);

	switch (axis)
	{
		// TODO: Add other deadzones
	case sf::Joystick::Axis::X:
	case sf::Joystick::Axis::Y:
		deadzone = 0.275f;
		break;
	default:
		deadzone = 0;
		break;
	}
	if (pos >= -deadzone*controls_.ANALOG_STICK_RADIUS && pos <= deadzone*controls_.ANALOG_STICK_RADIUS)
	{
		pos = 0;
	}

	return pos;
}

bool Controller::axisPercentageGreaterThan(sf::Joystick::Axis axis, float percent)
{
	float max;

	switch (axis)
	{
	case sf::Joystick::Axis::X:
	case sf::Joystick::Axis::Y:
	{
		max = controls_.ANALOG_STICK_RADIUS;
		if (percent < 0)
		{
			max *= -1;
		}
	}
	break;
	case sf::Joystick::Axis::V:
	case sf::Joystick::Axis::U:
	{
		max = controls_.C_STICK_RADIUS;
		if (percent < 0)
		{
			max *= -1;
		}
	}
	break;
	case sf::Joystick::Axis::Z:
	case sf::Joystick::Axis::R:
	{
		// TODO: This may be wrong
		if (percent < 0)
		{
			return true;
		}
		/*
		if (controls_.SHOULDER_MIN < 0)
		{
		max = controls_.SHOULDER_MAX - controls_.SHOULDER_MIN
		}
		else
		{
		max = controls_.SHOULDER_MAX - controls_.SHOULDER_MIN
		}
		*/
	}
	break;
	default:
		max = 0;
		break;
	}
	if (getAxisPosition(axis) > 0.01*percent*max)
	{
		return true;
	}
	else
	{
		return false;
	}
}

bool Controller::axisPercentageLessThan(sf::Joystick::Axis axis, float percent)
{
	float max;

	switch (axis)
	{
	case sf::Joystick::Axis::X:
	case sf::Joystick::Axis::Y:
	{
		max = controls_.ANALOG_STICK_RADIUS;
		if (percent < 0)
		{
			max *= -1;
		}
	}
	break;
	case sf::Joystick::Axis::V:
	case sf::Joystick::Axis::U:
	{
		max = controls_.C_STICK_RADIUS;
		if (percent < 0)
		{
			max *= -1;
		}
	}
	break;
	case sf::Joystick::Axis::Z:
	case sf::Joystick::Axis::R:
	{
		// this may be wrong
		if (percent >= 0)
		{
			max = controls_.SHOULDER_MAX;
		}
		else
		{
			max = controls_.SHOULDER_MIN;
		}
	}
	break;
	default:
		max = 0;
		break;
	}
	if (getAxisPosition(axis) < 0.01*percent*max)
	{
		return true;
	}
	else
	{
		return false;
	}
}

bool Controller::axisPercentageBetween(sf::Joystick::Axis axis, float percentOne, float percentTwo)
{
	if (percentOne > percentTwo)
	{
		float temp = percentOne;
		percentOne = percentTwo;
		percentTwo = temp;
	}
	if (axisPercentageGreaterThan(axis, percentOne) && axisPercentageLessThan(axis, percentTwo))
	{
		return true;
	}
	else
	{
		return false;
	}
}

int Controller::getControlStickAngle()
{
	float angle = -atan2f(getAxisPosition(sf::Joystick::Axis::Y), getAxisPosition(sf::Joystick::Axis::X)) * 180 / static_cast<float>(M_PI);
	return static_cast<int>(angle + 0.5);
}

bool Controller::buttonPressed(Button& button)
{
	if (sf::Joystick::isButtonPressed(controllerId_, button.id) && !button.held)
	{
		button.held = true;
		return true;
	}
	else
	{
		return false;
	}
}

void Controller::checkHeldButtons()
{
	if (controls_.A.held)
	{
		if (!sf::Joystick::isButtonPressed(controllerId_, controls_.A.id))
		{
			controls_.A.held = false;
		}
	}
	if (controls_.B.held)
	{
		if (!sf::Joystick::isButtonPressed(controllerId_, controls_.B.id))
		{
			controls_.B.held = false;
		}
	}
	if (controls_.X.held)
	{
		if (!sf::Joystick::isButtonPressed(controllerId_, controls_.X.id))
		{
			controls_.X.held = false;
		}
	}
	if (controls_.Y.held)
	{
		if (!sf::Joystick::isButtonPressed(controllerId_, controls_.Y.id))
		{
			controls_.Y.held = false;
		}
	}
	if (controls_.Z.held)
	{
		if (!sf::Joystick::isButtonPressed(controllerId_, controls_.Z.id))
		{
			controls_.Z.held = false;
		}
	}
	if (controls_.R.held)
	{
		if (!sf::Joystick::isButtonPressed(controllerId_, controls_.R.id))
		{
			controls_.R.held = false;
		}
	}
	if (controls_.L.held)
	{
		if (!sf::Joystick::isButtonPressed(controllerId_, controls_.L.id))
		{
			controls_.L.held = false;
		}
	}
	if (controls_.START.held)
	{
		if (!sf::Joystick::isButtonPressed(controllerId_, controls_.START.id))
		{
			controls_.START.held = false;
		}
	}
	if (controls_.D_PAD_UP.held)
	{
		if (!sf::Joystick::isButtonPressed(controllerId_, controls_.D_PAD_UP.id))
		{
			controls_.D_PAD_UP.held = false;
		}
	}
	if (controls_.D_PAD_LEFT.held)
	{
		if (!sf::Joystick::isButtonPressed(controllerId_, controls_.D_PAD_LEFT.id))
		{
			controls_.D_PAD_LEFT.held = false;
		}
	}
	if (controls_.D_PAD_DOWN.held)
	{
		if (!sf::Joystick::isButtonPressed(controllerId_, controls_.D_PAD_DOWN.id))
		{
			controls_.D_PAD_DOWN.held = false;
		}
	}
	if (controls_.D_PAD_RIGHT.held)
	{
		if (!sf::Joystick::isButtonPressed(controllerId_, controls_.D_PAD_RIGHT.id))
		{
			controls_.D_PAD_RIGHT.held = false;
		}
	}
}

void Controller::checkStickDirection()
{
	if (axisPercentageLessThan(sf::Joystick::Axis::Y, -25) && stickDirection_ != CardinalDirections::Up)
	{
		stickDirection_ = CardinalDirections::Up;
		framesSinceStickDirectionChange_ = 0;
	}
	else if (axisPercentageGreaterThan(sf::Joystick::Axis::Y, 25) && stickDirection_ != CardinalDirections::Down)
	{
		stickDirection_ = CardinalDirections::Down;
		framesSinceStickDirectionChange_ = 0;
	}
	else if (axisPercentageLessThan(sf::Joystick::Axis::X, -25) && stickDirection_ != CardinalDirections::Left)
	{
		stickDirection_ = CardinalDirections::Left;
		framesSinceStickDirectionChange_ = 0;
	}
	else if (axisPercentageGreaterThan(sf::Joystick::Axis::X, 25) && stickDirection_ != CardinalDirections::Right)
	{
		stickDirection_ = CardinalDirections::Right;
		framesSinceStickDirectionChange_ = 0;
	}
	// probably a better way to do this
	else if (axisPercentageGreaterThan(sf::Joystick::Axis::Y, -25) && axisPercentageLessThan(sf::Joystick::Axis::Y, 25) &&
		axisPercentageGreaterThan(sf::Joystick::Axis::X, -25) && axisPercentageLessThan(sf::Joystick::Axis::X, 25) &&
		stickDirection_ != CardinalDirections::None)
	{
		stickDirection_ = CardinalDirections::None;
		framesSinceStickDirectionChange_ = 0;
	}
	else
	{
		framesSinceStickDirectionChange_++;
	}
}
