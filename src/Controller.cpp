#include "Controller.h"

Controller::Controller() {}

Controller::Controller(unsigned int controllerId)
{
	controllerId_ = controllerId;
}

void Controller::update()
{
	checkStickDirections();
	checkHeldButtons();
}

void Controller::mapStick(StickName name, Axis x, Axis y, float radius)
{
	stickMap_.at(name) = { x, y, radius,{ 0, 0 }, CardinalDirections::None, CardinalDirections::None };
}

void Controller::mapShoulder(ShoulderName name, Axis axis, float min, float max)
{
	shoulderMap_.at(name) = { axis, min, max };
}

void Controller::mapButton(ButtonName name, unsigned int id)
{
	buttonMap_.at(name) = { id, false };
}

sf::Vector2f Controller::getStickPosition(StickName name) const
{
	float deadzone = 0.275f;
	Stick stick = stickMap_.at(name);
	sf::Vector2f pos;
	pos.x = sf::Joystick::getAxisPosition(controllerId_, stick.x);
	pos.y = sf::Joystick::getAxisPosition(controllerId_, stick.y);
	if (pos.x >= -deadzone*stick.radius && pos.x <= deadzone*stick.radius)
	{
		pos.x = 0;
	}
	if (pos.y >= -deadzone*stick.radius && pos.y <= deadzone*stick.radius)
	{
		pos.y = 0;
	}
	return pos;
}

sf::Vector2f Controller::getStickPositionPercentage(StickName name) const
{
	Stick stick = stickMap_.at(name);
	sf::Vector2f pos = getStickPosition(name);
	pos.x *= 100 / stick.radius;
	pos.y *= 100 / stick.radius;
	if (pos.x > 100)
	{
		pos.x = 100;
	}
	if (pos.y > 100)
	{
		pos.y = 100;
	}
	return pos;
}

int Controller::getStickAngle(StickName name) const
{
	Stick stick = stickMap_.at(name);
	sf::Vector2f pos = getStickPosition(name);
	// -atan due to SFML's Y-axis orientation
	float angle = -atan2f(pos.y, pos.x) * 180 / static_cast<float>(M_PI);
	// Add 0.5 to fix rounding truncation and add 360 followed by modulo 360 to always get a positive angle
	return static_cast<int>(angle + 0.5 + 360) % 360;
}

sf::Vector2f Controller::getFramesSinceDirectionChange(StickName name) const
{
	return stickMap_.at(name).framesSinceChange;
}

float Controller::getShoulderPosition(ShoulderName name) const
{
	float deadzone = 0.30f; // TODO: check this
	Shoulder shoulder = shoulderMap_.at(name);
	float pos = sf::Joystick::getAxisPosition(controllerId_, shoulder.axis);
	pos -= shoulder.min;
	if (pos > deadzone*(shoulder.max - shoulder.min)) // TODO: test
	{
		pos = shoulder.min;
	}
	return pos;
}

float Controller::getShoulderPositionPercentage(ShoulderName name) const
{
	Shoulder shoulder = shoulderMap_.at(name);
	float pos = getShoulderPosition(name);
	pos -= shoulder.min;
	pos *= 100 / (shoulder.max - shoulder.min); // TODO: test
	if (pos > 100)
	{
		pos = 100;
	}
	return pos;
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

void Controller::checkStickDirections()
{
	// Update the state of the control stick X-axis
	if (getStickPosition(StickName::CONTROL_STICK).x < -25)
	{
		if (stickMap_.at(StickName::CONTROL_STICK).horizontalDir != CardinalDirections::Left)
		{
			stickMap_.at(StickName::CONTROL_STICK).horizontalDir = CardinalDirections::Left;
			stickMap_.at(StickName::CONTROL_STICK).framesSinceChange.x = 0;
		}
		else
		{
			stickMap_.at(StickName::CONTROL_STICK).framesSinceChange.x++;
		}
	}
	else if (getStickPosition(StickName::CONTROL_STICK).x > 25)
	{
		if (stickMap_.at(StickName::CONTROL_STICK).horizontalDir != CardinalDirections::Right)
		{
			stickMap_.at(StickName::CONTROL_STICK).horizontalDir = CardinalDirections::Right;
			stickMap_.at(StickName::CONTROL_STICK).framesSinceChange.x = 0;
		}
		else
		{
			stickMap_.at(StickName::CONTROL_STICK).framesSinceChange.x++;
		}
	}
	else
	{
		stickMap_.at(StickName::CONTROL_STICK).horizontalDir = CardinalDirections::None;
		stickMap_.at(StickName::CONTROL_STICK).framesSinceChange.x = 0;
	}
	// Update the state of the control stick Y-axis
	if (getStickPosition(StickName::CONTROL_STICK).y < -25)
	{
		if (stickMap_.at(StickName::CONTROL_STICK).verticalDir != CardinalDirections::Up)
		{
			stickMap_.at(StickName::CONTROL_STICK).verticalDir = CardinalDirections::Up;
			stickMap_.at(StickName::CONTROL_STICK).framesSinceChange.y = 0;
		}
		else
		{
			stickMap_.at(StickName::CONTROL_STICK).framesSinceChange.y++;
		}
	}
	else if (getStickPosition(StickName::CONTROL_STICK).y > 25)
	{
		if (stickMap_.at(StickName::CONTROL_STICK).verticalDir != CardinalDirections::Down)
		{
			stickMap_.at(StickName::CONTROL_STICK).verticalDir = CardinalDirections::Down;
			stickMap_.at(StickName::CONTROL_STICK).framesSinceChange.y = 0;
		}
		else
		{
			stickMap_.at(StickName::CONTROL_STICK).framesSinceChange.y++;
		}
	}
	else
	{
		stickMap_.at(StickName::CONTROL_STICK).verticalDir = CardinalDirections::None;
		stickMap_.at(StickName::CONTROL_STICK).framesSinceChange.y = 0;
	}
	// Update the state of the c stick X-axis
	if (getStickPosition(StickName::C_STICK).x < -25)
	{
		if (stickMap_.at(StickName::C_STICK).horizontalDir != CardinalDirections::Left)
		{
			stickMap_.at(StickName::C_STICK).horizontalDir = CardinalDirections::Left;
			stickMap_.at(StickName::C_STICK).framesSinceChange.x = 0;
		}
		else
		{
			stickMap_.at(StickName::C_STICK).framesSinceChange.x++;
		}
	}
	else if (getStickPosition(StickName::C_STICK).x > 25)
	{
		if (stickMap_.at(StickName::C_STICK).horizontalDir != CardinalDirections::Right)
		{
			stickMap_.at(StickName::C_STICK).horizontalDir = CardinalDirections::Right;
			stickMap_.at(StickName::C_STICK).framesSinceChange.x = 0;
		}
		else
		{
			stickMap_.at(StickName::C_STICK).framesSinceChange.x++;
		}
	}
	else
	{
		stickMap_.at(StickName::C_STICK).horizontalDir = CardinalDirections::None;
		stickMap_.at(StickName::C_STICK).framesSinceChange.x = 0;
	}
	// Update the state of the c stick Y-axis
	if (getStickPosition(StickName::C_STICK).y < -25)
	{
		if (stickMap_.at(StickName::C_STICK).verticalDir != CardinalDirections::Up)
		{
			stickMap_.at(StickName::C_STICK).verticalDir = CardinalDirections::Up;
			stickMap_.at(StickName::C_STICK).framesSinceChange.y = 0;
		}
		else
		{
			stickMap_.at(StickName::C_STICK).framesSinceChange.y++;
		}
	}
	else if (getStickPosition(StickName::C_STICK).y > 25)
	{
		if (stickMap_.at(StickName::C_STICK).verticalDir != CardinalDirections::Down)
		{
			stickMap_.at(StickName::C_STICK).verticalDir = CardinalDirections::Down;
			stickMap_.at(StickName::C_STICK).framesSinceChange.y = 0;
		}
		else
		{
			stickMap_.at(StickName::C_STICK).framesSinceChange.y++;
		}
	}
	else
	{
		stickMap_.at(StickName::C_STICK).verticalDir = CardinalDirections::None;
		stickMap_.at(StickName::C_STICK).framesSinceChange.y = 0;
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