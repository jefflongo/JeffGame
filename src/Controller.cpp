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

void Controller::mapStick(StickName name, Axis x, Axis y, float radius, float deadzone)
{
	// To avoid division by 0
	if (radius == 0)
	{
		radius = 1;
	}
	stickMap_[name] = { x, y, abs(radius), deadzone, { 0, 0 }, CardinalDirections::None, CardinalDirections::None };
}

void Controller::mapShoulder(ShoulderName name, Axis axis, float min, float max, float deadzone)
{
	// To avoid division by 0
	if (min == max)
	{
		min = max - 1;
	}
	shoulderMap_[name] = { axis, min, max, deadzone };
}

void Controller::mapButton(ButtonName name, unsigned int id)
{
	buttonMap_[name] = { id, false };
}

sf::Vector2f Controller::getStickPosition(StickName name) const
{
	Stick stick = stickMap_.at(name);
	sf::Vector2f pos;
	pos.x = sf::Joystick::getAxisPosition(controllerId_, stick.x);
	pos.y = sf::Joystick::getAxisPosition(controllerId_, stick.y);
	pos /= stick.radius;

	float mag = sqrt(pos.x*pos.x + pos.y*pos.y);
	// If the magnitude of the stick position vector is outside the circular range of inputs,
	// normalize it, by giving it a magnitude of 1 which will lie on the perimeter of the circle
	if (mag > 1)
	{
		pos /= mag;
	}
	if (abs(pos.x) <= stick.deadzone)
	{
		pos.x = 0;
	}
	if (abs(pos.y) <= stick.deadzone)
	{
		pos.y = 0;
	}
	return pos;
}

float Controller::getShoulderPosition(ShoulderName name) const
{
	Shoulder shoulder = shoulderMap_.at(name);
	float pos = (sf::Joystick::getAxisPosition(controllerId_, shoulder.axis) - shoulder.min) / (shoulder.max - shoulder.min);
	if (pos <= shoulder.deadzone)
	{
		pos = 0;
	}
	else if (pos > 1)
	{
		pos = 1;
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

sf::Vector2u Controller::getFramesSinceDirectionChange(StickName name) const
{
	return stickMap_.at(name).framesSinceChange;
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
	// Iterate through the map
	for (auto& i : stickMap_)
	{
		sf::Vector2f pos = getStickPosition(i.first);
		// Update the state of the x-axis
		if (pos.x <= -0.25)
		{
			if (i.second.horizontalDir != CardinalDirections::Left)
			{
				i.second.horizontalDir = CardinalDirections::Left;
				i.second.framesSinceChange.x = 0;
			}
			else
			{
				i.second.framesSinceChange.x++;
			}
		}
		else if (pos.x >= 0.25)
		{
			if (i.second.horizontalDir != CardinalDirections::Right)
			{
				i.second.horizontalDir = CardinalDirections::Right;
				i.second.framesSinceChange.x = 0;
			}
			else
			{
				i.second.framesSinceChange.x++;
			}
		}
		else
		{
			if (i.second.horizontalDir != CardinalDirections::None)
			{
				i.second.horizontalDir = CardinalDirections::None;
				i.second.framesSinceChange.x = 0;
			}
			else
			{
				i.second.framesSinceChange.x++;
			}
		}
		// Update the state of the y-axis
		if (pos.y <= -0.25)
		{
			if (i.second.verticalDir != CardinalDirections::Up)
			{
				i.second.verticalDir = CardinalDirections::Up;
				i.second.framesSinceChange.y = 0;
			}
			else
			{
				i.second.framesSinceChange.y++;
			}
		}
		else if (pos.y >= 0.25)
		{
			if (i.second.verticalDir != CardinalDirections::Down)
			{
				i.second.verticalDir = CardinalDirections::Down;
				i.second.framesSinceChange.y = 0;
			}
			else
			{
				i.second.framesSinceChange.y++;
			}
		}
		else
		{
			if (i.second.verticalDir != CardinalDirections::None)
			{
				i.second.verticalDir = CardinalDirections::None;
				i.second.framesSinceChange.y = 0;
			}
			else
			{
				i.second.framesSinceChange.y++;
			}
		}
	}
}

void Controller::checkHeldButtons()
{
	// Iterate through the map
	for (auto& i : buttonMap_)
	{
		// If the button is not held and its state is currently held, update the state
		if (!sf::Joystick::isButtonPressed(controllerId_, i.second.id) && i.second.held)
		{
			i.second.held = false;
		}
	}
}