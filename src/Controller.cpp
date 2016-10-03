#include "Controller.h"

Controller::Controller(){}

Controller::Controller(unsigned int controllerId)
{
	controllerId_ = controllerId;
}

void Controller::update()
{
	checkHeldButtons();
	checkStickDirections();
}

void Controller::setControlStick(float radius)
{
	CONTROL_STICK_.radius = radius;
	CONTROL_STICK_.framesSinceHorizontalChange = CONTROL_STICK_.framesSinceVerticalChange = 0;
	CONTROL_STICK_.horizontalDir = CONTROL_STICK_.verticalDir = CardinalDirections::None;
}

void Controller::setCStick(float radius)
{
	C_STICK_.radius = radius;
	C_STICK_.framesSinceHorizontalChange = C_STICK_.framesSinceVerticalChange = 0;
	C_STICK_.horizontalDir = C_STICK_.verticalDir = CardinalDirections::None;
}

void Controller::setShoulderAnalog(float min, float max)
{
	SHOULDER_MIN_ = min;
	SHOULDER_MAX_ = max;
}

void Controller::mapKey(ButtonName name, unsigned int id)
{
	buttonMap_.at(name) = { id, false };
}

float Controller::getAxisPosition(Axis axis) const
{
	float pos = sf::Joystick::getAxisPosition(controllerId_, axis), deadzone = 0;

	switch (axis)
	{
	case Axis::X:
	case Axis::Y:
		deadzone = 0.275f;
		if (pos >= -deadzone*CONTROL_STICK_.radius && pos <= deadzone*CONTROL_STICK_.radius)
		{
			pos = 0;
		}
		break;
	case Axis::V:
	case Axis::U:
		deadzone = 0.275f;
		if (pos >= -deadzone*C_STICK_.radius && pos <= deadzone*C_STICK_.radius)
		{
			pos = 0;
		}
		break;
		break;
	case sf::Joystick::Axis::Z:
	case sf::Joystick::Axis::R:
		// TODO: Add deadzone, 0.30
		pos -= SHOULDER_MIN_;
		break;
	default:
		break;
	}
	return pos;
}

int Controller::getControlStickAngle() const
{
	// -atan due to SFML's Y-axis orientation
	float angle = -atan2f(getAxisPosition(Axis::Y), getAxisPosition(Axis::X)) * 180 / static_cast<float>(M_PI);
	// Add 0.5 to fix rounding truncation and add 360 followed by modulo 360 to always get a positive angle
	return static_cast<int>(angle + 0.5 + 360) % 360;
}

bool Controller::buttonPressed(ButtonName name)
{
	Button& button = buttonMap_.at(name);
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

bool Controller::axisPercentageGreaterThan(Axis axis, float percent)
{
	float max;

	switch (axis)
	{
	case sf::Joystick::Axis::X:
	case sf::Joystick::Axis::Y:
	{
		max = CONTROL_STICK_.radius;
	}
	break;
	case sf::Joystick::Axis::V:
	case sf::Joystick::Axis::U:
	{
		max = C_STICK_.radius;
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
		max = SHOULDER_MAX_ - SHOULDER_MIN_;
	}
	break;
	default:
		max = 0;
		break;
	}
	return (getAxisPosition(axis) > 0.01*percent*max) ? true : false;
}

bool Controller::axisPercentageLessThan(sf::Joystick::Axis axis, float percent)
{
	float max;

	switch (axis)
	{
	case sf::Joystick::Axis::X:
	case sf::Joystick::Axis::Y:
	{
		max = CONTROL_STICK_.radius;
	}
	break;
	case sf::Joystick::Axis::V:
	case sf::Joystick::Axis::U:
	{
		max = C_STICK_.radius;
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
		max = SHOULDER_MAX_ - SHOULDER_MIN_;
	}
	break;
	default:
		max = 0;
		break;
	}
	return (getAxisPosition(axis) < 0.01*percent*max) ? true : false;
}

bool Controller::axisPercentageBetween(Axis axis, float percentOne, float percentTwo)
{
	if (percentOne > percentTwo)
	{
		float temp = percentOne;
		percentOne = percentTwo;
		percentTwo = temp;
	}
	return (axisPercentageGreaterThan(axis, percentOne) && axisPercentageLessThan(axis, percentTwo)) ? true : false;
}

bool Controller::controlStickAngleBetween(int angleOne, int angleTwo)
{
	if (angleOne > angleTwo)
	{
		int temp = angleOne;
		angleOne = angleTwo;
		angleTwo = temp;
	}
	return (getControlStickAngle() >= angleOne && getControlStickAngle() <= angleTwo) ? true : false;
}

bool Controller::cardinalDirectionChange(Axis axis, int frames)
{
	switch (axis)
	{
	case Axis::X:
		return (CONTROL_STICK_.framesSinceHorizontalChange <= frames) ? true : false;
		break;
	case Axis::Y:
		return (CONTROL_STICK_.framesSinceVerticalChange <= frames) ? true : false;
		break;
	case Axis::V:
		return (C_STICK_.framesSinceHorizontalChange <= frames) ? true : false;
		break;
	case Axis::U:
		return (C_STICK_.framesSinceVerticalChange <= frames) ? true : false;
		break;
	default:
		return false;
		break;
	}
}

void Controller::checkHeldButtons()
{
	if (buttonMap_.at(ButtonName::A).held)
	{
		if (!sf::Joystick::isButtonPressed(controllerId_, buttonMap_.at(ButtonName::A).id))
		{
			buttonMap_.at(ButtonName::A).held = false;
		}
	}
	if (buttonMap_.at(ButtonName::B).held)
	{
		if (!sf::Joystick::isButtonPressed(controllerId_, buttonMap_.at(ButtonName::B).id))
		{
			buttonMap_.at(ButtonName::B).held = false;
		}
	}
	if (buttonMap_.at(ButtonName::X).held)
	{
		if (!sf::Joystick::isButtonPressed(controllerId_, buttonMap_.at(ButtonName::X).id))
		{
			buttonMap_.at(ButtonName::X).held = false;
		}
	}
	if (buttonMap_.at(ButtonName::Y).held)
	{
		if (!sf::Joystick::isButtonPressed(controllerId_, buttonMap_.at(ButtonName::Y).id))
		{
			buttonMap_.at(ButtonName::Y).held = false;
		}
	}

	if (buttonMap_.at(ButtonName::Z).held)
	{
		if (!sf::Joystick::isButtonPressed(controllerId_, buttonMap_.at(ButtonName::Z).id))
		{
			buttonMap_.at(ButtonName::Z).held = false;
		}
	}
	if (buttonMap_.at(ButtonName::R).held)
	{
		if (!sf::Joystick::isButtonPressed(controllerId_, buttonMap_.at(ButtonName::R).id))
		{
			buttonMap_.at(ButtonName::R).held = false;
		}
	}
	if (buttonMap_.at(ButtonName::L).held)
	{
		if (!sf::Joystick::isButtonPressed(controllerId_, buttonMap_.at(ButtonName::L).id))
		{
			buttonMap_.at(ButtonName::L).held = false;
		}
	}
	if (buttonMap_.at(ButtonName::START).held)
	{
		if (!sf::Joystick::isButtonPressed(controllerId_, buttonMap_.at(ButtonName::START).id))
		{
			buttonMap_.at(ButtonName::START).held = false;
		}
	}
	if (buttonMap_.at(ButtonName::D_PAD_UP).held)
	{
		if (!sf::Joystick::isButtonPressed(controllerId_, buttonMap_.at(ButtonName::D_PAD_UP).id))
		{
			buttonMap_.at(ButtonName::D_PAD_UP).held = false;
		}
	}
	if (buttonMap_.at(ButtonName::D_PAD_LEFT).held)
	{
		if (!sf::Joystick::isButtonPressed(controllerId_, buttonMap_.at(ButtonName::D_PAD_LEFT).id))
		{
			buttonMap_.at(ButtonName::D_PAD_LEFT).held = false;
		}
	}
	if (buttonMap_.at(ButtonName::D_PAD_DOWN).held)
	{
		if (!sf::Joystick::isButtonPressed(controllerId_, buttonMap_.at(ButtonName::D_PAD_DOWN).id))
		{
			buttonMap_.at(ButtonName::D_PAD_DOWN).held = false;
		}
	}
	if (buttonMap_.at(ButtonName::D_PAD_RIGHT).held)
	{
		if (!sf::Joystick::isButtonPressed(controllerId_, buttonMap_.at(ButtonName::D_PAD_RIGHT).id))
		{
			buttonMap_.at(ButtonName::D_PAD_RIGHT).held = false;
		}
	}
}

void Controller::checkStickDirections()
{
	// Update the state of the X-axis
	if (axisPercentageLessThan(Axis::X, -25))
	{
		if (CONTROL_STICK_.horizontalDir != CardinalDirections::Left)
		{
			CONTROL_STICK_.horizontalDir = CardinalDirections::Left;
			CONTROL_STICK_.framesSinceHorizontalChange = 0;
		}
		else
		{
			CONTROL_STICK_.framesSinceHorizontalChange++;
		}
	}
	else if (axisPercentageGreaterThan(Axis::X, 25))
	{
		if (CONTROL_STICK_.horizontalDir != CardinalDirections::Right)
		{
			CONTROL_STICK_.horizontalDir = CardinalDirections::Right;
			CONTROL_STICK_.framesSinceHorizontalChange = 0;
		}
		else
		{
			CONTROL_STICK_.framesSinceHorizontalChange++;
		}
	}
	else
	{
		CONTROL_STICK_.horizontalDir = CardinalDirections::None;
		CONTROL_STICK_.framesSinceHorizontalChange = 0;
	}
	// Update the state of the Y-axis
	if (axisPercentageLessThan(Axis::Y, -25))
	{
		if (CONTROL_STICK_.verticalDir != CardinalDirections::Up)
		{
			CONTROL_STICK_.verticalDir = CardinalDirections::Up;
			CONTROL_STICK_.framesSinceVerticalChange = 0;
		}
		else
		{
			CONTROL_STICK_.framesSinceVerticalChange++;
		}
	}
	else if (axisPercentageGreaterThan(Axis::Y, 25))
	{
		if (CONTROL_STICK_.verticalDir != CardinalDirections::Down)
		{
			CONTROL_STICK_.verticalDir = CardinalDirections::Down;
			CONTROL_STICK_.framesSinceVerticalChange = 0;
		}
		else
		{
			CONTROL_STICK_.framesSinceVerticalChange++;
		}
	}
	else
	{
		CONTROL_STICK_.verticalDir = CardinalDirections::None;
		CONTROL_STICK_.framesSinceVerticalChange = 0;
	}
	// Update the state of the V-axis
	if (axisPercentageLessThan(Axis::V, -25))
	{
		if (C_STICK_.horizontalDir != CardinalDirections::Left)
		{
			C_STICK_.horizontalDir = CardinalDirections::Left;
			C_STICK_.framesSinceHorizontalChange = 0;
		}
		else
		{
			C_STICK_.framesSinceHorizontalChange++;
		}
	}
	else if (axisPercentageGreaterThan(Axis::V, 25))
	{
		if (C_STICK_.horizontalDir != CardinalDirections::Right)
		{
			C_STICK_.horizontalDir = CardinalDirections::Right;
			C_STICK_.framesSinceHorizontalChange = 0;
		}
		else
		{
			C_STICK_.framesSinceHorizontalChange++;
		}
	}
	else
	{
		C_STICK_.horizontalDir = CardinalDirections::None;
		C_STICK_.framesSinceHorizontalChange = 0;
	}
	// Update the state of the U-axis
	if (axisPercentageLessThan(Axis::U, -25))
	{
		if (C_STICK_.verticalDir != CardinalDirections::Up)
		{
			C_STICK_.verticalDir = CardinalDirections::Up;
			C_STICK_.framesSinceVerticalChange = 0;
		}
		else
		{
			C_STICK_.framesSinceVerticalChange++;
		}
	}
	else if (axisPercentageGreaterThan(Axis::U, 25))
	{
		if (C_STICK_.verticalDir != CardinalDirections::Down)
		{
			C_STICK_.verticalDir = CardinalDirections::Down;
			C_STICK_.framesSinceVerticalChange = 0;
		}
		else
		{
			C_STICK_.framesSinceVerticalChange++;
		}
	}
	else
	{
		C_STICK_.verticalDir = CardinalDirections::None;
		C_STICK_.framesSinceVerticalChange = 0;
	}
}