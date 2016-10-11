#include "SplashScreen.h"

#include <iostream>
#include "../Globals.h"
#include "../Game.h"
#include "../Controller.h"
#include "Battle.h"

void SplashScreen::init()
{
	std::cout << "SplashScreen initialized.\n";

	connectedDevices_ = getConnectedDevices();

	theme_.openFromFile("res/audio/theme.ogg");
	font_.loadFromFile("res/fonts/PressStart2P.ttf");
	pressStartText_.setFont(font_);
	pressStartText_.setString("Press Start");
	pressStartText_.setOrigin(0.5f*pressStartText_.getGlobalBounds().width, 0.5f*pressStartText_.getGlobalBounds().height);
	pressStartText_.setPosition(sf::Vector2f(0.5f*Globals::WINDOW_WIDTH, 0.2f*Globals::WINDOW_HEIGHT));

	theme_.setLoop(true);
	theme_.play();
}

void SplashScreen::update(Game& game)
{
	moveText();
	pollForStart(game);
}

void SplashScreen::render(sf::RenderWindow& window)
{
	window.draw(pressStartText_);
}

void SplashScreen::destroy()
{
	theme_.stop();
}

void SplashScreen::pollForStart(Game& game)
{
	const static int NUM_OF_BUTTONS = 11;
	static bool startPressed = false;
	static Controller* controller = nullptr; // TODO: when do we delete this??

	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Return))
	{
		startPressed = true;
	}

	// Check all available devices
	for (unsigned int i : connectedDevices_)
	{
		// Check the current device for a gamecube controller
		if (sf::Joystick::getIdentification(i).name.toAnsiString() == "vJoy Device")
		{
			// Check for a start button press
			if (sf::Joystick::isButtonPressed(i, 7))
			{
				controller = new Controller(i);
				controller->mapStick(StickName::CONTROL_STICK, sf::Joystick::Axis::X, sf::Joystick::Axis::Y, 80.0f, 0.275f);
				controller->mapStick(StickName::C_STICK, sf::Joystick::Axis::V, sf::Joystick::Axis::U, 80.0f, 0.275f);
				controller->mapShoulder(ShoulderName::L, sf::Joystick::Axis::Z, -100.0f, 60.0f, 0.3f);
				controller->mapShoulder(ShoulderName::R, sf::Joystick::Axis::R, -100.0f, 60.0f, 0.3f);
				controller->mapButton(ButtonName::A, 0);
				controller->mapButton(ButtonName::B, 1);
				controller->mapButton(ButtonName::X, 2);
				controller->mapButton(ButtonName::Y, 3);
				controller->mapButton(ButtonName::Z, 4);
				controller->mapButton(ButtonName::R, 5);
				controller->mapButton(ButtonName::L, 6);
				controller->mapButton(ButtonName::START, 7);
				controller->mapButton(ButtonName::D_PAD_UP, 8);
				controller->mapButton(ButtonName::D_PAD_LEFT, 9);
				controller->mapButton(ButtonName::D_PAD_DOWN, 10);
				controller->mapButton(ButtonName::D_PAD_RIGHT, 11);
				startPressed = true;
				break;
			}
		}
		// Check the current device for a PS3 controller
		else if (sf::Joystick::getIdentification(i).name.toAnsiString() == "Controller (XBOX 360 For Windows)")
		{
			// Check for a start button press
			if (sf::Joystick::isButtonPressed(i, 7))
			{
				controller = new Controller(i);
				controller->mapStick(StickName::CONTROL_STICK, sf::Joystick::Axis::X, sf::Joystick::Axis::Y, 100.0f, 0.275f);
				controller->mapStick(StickName::C_STICK, sf::Joystick::Axis::V, sf::Joystick::Axis::U, 100.0f, 0.275f);
				controller->mapShoulder(ShoulderName::L, sf::Joystick::Axis::Z, 0, 60.0f, 0.3f);
				controller->mapShoulder(ShoulderName::R, sf::Joystick::Axis::R, 0, 100.0f, 0.3f);
				controller->mapButton(ButtonName::A, 0);
				controller->mapButton(ButtonName::B, 2);
				controller->mapButton(ButtonName::X, 1);
				controller->mapButton(ButtonName::Y, 3);
				controller->mapButton(ButtonName::Z, 5);
				controller->mapButton(ButtonName::R, 4);
				controller->mapButton(ButtonName::L, 6);
				controller->mapButton(ButtonName::START, 7);
				controller->mapButton(ButtonName::D_PAD_UP, 8);
				controller->mapButton(ButtonName::D_PAD_LEFT, 9);
				controller->mapButton(ButtonName::D_PAD_DOWN, 10);
				controller->mapButton(ButtonName::D_PAD_RIGHT, 11);
				startPressed = true;
				break;
			}
		}
	}
	if (startPressed)
	{
		static int vol = 100, fadeTimer = 100;
		if (--vol > 0)
		{
			theme_.setVolume(static_cast<float>(vol));
		}
		if (fadeTimer-- == 0)
		{
			game.setState(new Battle(controller));
		}
	}
}

std::vector<unsigned int> SplashScreen::getConnectedDevices()
{
	std::vector<unsigned int> connectedDevices;
	for (int i = 0; i < 10; i++)
	{
		if (sf::Joystick::isConnected(i))
		{
			connectedDevices.push_back(i);
			i++;
		}
	}
	return connectedDevices;
}

void SplashScreen::moveText()
{
	static bool moveDown = true;
	static int counter = 80;

	if (moveDown)
	{
		pressStartText_.move(0, 1);
	}
	else
	{
		pressStartText_.move(0, -1);
	}
	counter--;
	if (counter == 0)
	{
		counter = 80;
		moveDown = !moveDown;
	}
}