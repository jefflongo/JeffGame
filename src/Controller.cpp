#include "Controller.h"

Controller::Controller(){}

Controller::Controller(unsigned int controllerId, Controls controls)
{
	controllerId_ = controllerId;
	controls_ = controls;
}

Controls* Controller::getControls()
{
	return &controls_;
}

void Controller::update()
{
	checkHeldButtons();
	checkStickDirections();
}

float Controller::getAxisPosition(Axis axis) const
{
	float pos = sf::Joystick::getAxisPosition(controllerId_, axis), deadzone = 0;

	switch (axis)
	{
	case Axis::X:
	case Axis::Y:
		deadzone = 0.275f;
		if (pos >= -deadzone*controls_.ANALOG_STICK_RADIUS && pos <= deadzone*controls_.ANALOG_STICK_RADIUS)
		{
			pos = 0;
		}
		break;
	case Axis::V:
	case Axis::U:
		deadzone = 0.275f;
		if (pos >= -deadzone*controls_.C_STICK_RADIUS && pos <= deadzone*controls_.C_STICK_RADIUS)
		{
			pos = 0;
		}
		break;
		break;
	case sf::Joystick::Axis::Z:
	case sf::Joystick::Axis::R:
		// TODO: Add deadzone, 0.30
		pos -= controls_.SHOULDER_MIN;
		break;
	default:
		break;
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
	}
	break;
	case sf::Joystick::Axis::V:
	case sf::Joystick::Axis::U:
	{
		max = controls_.C_STICK_RADIUS;
	}
	break;
	case sf::Joystick::Axis::Z:
	case sf::Joystick::Axis::R:
	{
		// TODO: Test
		if (percent < 0)
		{
			return true;
		}
		max = controls_.SHOULDER_MAX - controls_.SHOULDER_MIN;
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
	}
	break;
	case sf::Joystick::Axis::V:
	case sf::Joystick::Axis::U:
	{
		max = controls_.C_STICK_RADIUS;
	}
	break;
	case sf::Joystick::Axis::Z:
	case sf::Joystick::Axis::R:
	{
		// TODO: Test
		if (percent < 0)
		{
			return true;
		}
		max = controls_.SHOULDER_MAX - controls_.SHOULDER_MIN;
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
	// -atan due to SFML's Y-axis orientation
	float angle = -atan2f(getAxisPosition(sf::Joystick::Axis::Y), getAxisPosition(sf::Joystick::Axis::X)) * 180 / static_cast<float>(M_PI);
	// Add 0.5 to fix rounding truncation and add 360 followed by modulo 360 to always get a positive angle
	return static_cast<int>(angle + 0.5 + 360) % 360;
}

bool Controller::controlStickAngleBetween(int angleOne, int angleTwo)
{
	if (angleOne > angleTwo)
	{
		int temp = angleOne;
		angleOne = angleTwo;
		angleTwo = temp;
	}
	if (getControlStickAngle() >= angleOne && getControlStickAngle() <= angleTwo)
	{
		return true;
	}
	else
	{
		return false;
	}
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

bool Controller::cardinalDirectionChange(Axis axis, int frames)
{
	switch (axis)
	{
	case Axis::X:
		if (controlStick_.framesSinceHorizontalChange <= frames)
		{
			return true;
		}
		else
		{
			return false;
		}
		break;
	case Axis::Y:
		if (controlStick_.framesSinceVerticalChange <= frames)
		{
			return true;
		}
		else
		{
			return false;
		}
		break;
	case Axis::V:
		if (cStick_.framesSinceHorizontalChange <= frames)
		{
			return true;
		}
		else
		{
			return false;
		}
		break;
	case Axis::U:
		if (cStick_.framesSinceVerticalChange <= frames)
		{
			return true;
		}
		else
		{
			return false;
		}
		break;
	default:
		return false;
		break;
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

void Controller::checkStickDirections()
{
	// Update the state of the X-axis
	if (axisPercentageLessThan(Axis::X, -25))
	{
		if (controlStick_.horizontalDir != CardinalDirections::Left)
		{
			controlStick_.horizontalDir = CardinalDirections::Left;
			controlStick_.framesSinceHorizontalChange = 0;
		}
		else
		{
			controlStick_.framesSinceHorizontalChange++;
		}
	}
	else if (axisPercentageGreaterThan(Axis::X, 25))
	{
		if (controlStick_.horizontalDir != CardinalDirections::Right)
		{
			controlStick_.horizontalDir = CardinalDirections::Right;
			controlStick_.framesSinceHorizontalChange = 0;
		}
		else
		{
			controlStick_.framesSinceHorizontalChange++;
		}
	}
	else
	{
		controlStick_.horizontalDir = CardinalDirections::None;
		controlStick_.framesSinceHorizontalChange = 0;
	}
	// Update the state of the Y-axis
	if (axisPercentageLessThan(Axis::Y, -25))
	{
		if (controlStick_.verticalDir != CardinalDirections::Up)
		{
			controlStick_.verticalDir = CardinalDirections::Up;
			controlStick_.framesSinceVerticalChange = 0;
		}
		else
		{
			controlStick_.framesSinceVerticalChange++;
		}
	}
	else if (axisPercentageGreaterThan(Axis::Y, 25))
	{
		if (controlStick_.verticalDir != CardinalDirections::Down)
		{
			controlStick_.verticalDir = CardinalDirections::Down;
			controlStick_.framesSinceVerticalChange = 0;
		}
		else
		{
			controlStick_.framesSinceVerticalChange++;
		}
	}
	else
	{
		controlStick_.verticalDir = CardinalDirections::None;
		controlStick_.framesSinceVerticalChange = 0;
	}
	// Update the state of the V-axis
	if (axisPercentageLessThan(Axis::V, -25))
	{
		if (cStick_.horizontalDir != CardinalDirections::Left)
		{
			cStick_.horizontalDir = CardinalDirections::Left;
			cStick_.framesSinceHorizontalChange = 0;
		}
		else
		{
			cStick_.framesSinceHorizontalChange++;
		}
	}
	else if (axisPercentageGreaterThan(Axis::V, 25))
	{
		if (cStick_.horizontalDir != CardinalDirections::Right)
		{
			cStick_.horizontalDir = CardinalDirections::Right;
			cStick_.framesSinceHorizontalChange = 0;
		}
		else
		{
			cStick_.framesSinceHorizontalChange++;
		}
	}
	else
	{
		cStick_.horizontalDir = CardinalDirections::None;
		cStick_.framesSinceHorizontalChange = 0;
	}
	// Update the state of the U-axis
	if (axisPercentageLessThan(Axis::U, -25))
	{
		if (cStick_.verticalDir != CardinalDirections::Up)
		{
			cStick_.verticalDir = CardinalDirections::Up;
			cStick_.framesSinceVerticalChange = 0;
		}
		else
		{
			cStick_.framesSinceVerticalChange++;
		}
	}
	else if (axisPercentageGreaterThan(Axis::U, 25))
	{
		if (cStick_.verticalDir != CardinalDirections::Down)
		{
			cStick_.verticalDir = CardinalDirections::Down;
			cStick_.framesSinceVerticalChange = 0;
		}
		else
		{
			cStick_.framesSinceVerticalChange++;
		}
	}
	else
	{
		cStick_.verticalDir = CardinalDirections::None;
		cStick_.framesSinceVerticalChange = 0;
	}
}
