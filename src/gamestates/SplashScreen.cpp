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
	static Controller* controller = nullptr; // TODO: when do we delete this??
	static bool startPressed = false;

	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Return))
	{
		startPressed = true;
	}

	// Check all available devices
	for (unsigned int i = 0; i < 6; i++) // TODO: connectedDevices_
	{
		// Check the current device for a gamecube controller
		if (sf::Joystick::getIdentification(i).name.toAnsiString() == "vJoy Device")
		{
			// Check for a start button press
			if (sf::Joystick::isButtonPressed(i, 7))
			{
				controller = new Controller(i);
				controller->setControlStick(80.0);
				controller->setCStick(50.0);
				controller->mapKey(Controller::ButtonName::A, 0);
				controller->mapKey(Controller::ButtonName::B, 1);
				controller->mapKey(Controller::ButtonName::X, 2);
				controller->mapKey(Controller::ButtonName::Y, 3);
				controller->mapKey(Controller::ButtonName::Z, 4);
				controller->mapKey(Controller::ButtonName::R, 5);
				controller->mapKey(Controller::ButtonName::L, 6);
				controller->mapKey(Controller::ButtonName::START, 7);
				controller->mapKey(Controller::ButtonName::D_PAD_UP, 8);
				controller->mapKey(Controller::ButtonName::D_PAD_LEFT, 9);
				controller->mapKey(Controller::ButtonName::D_PAD_DOWN, 10);
				controller->mapKey(Controller::ButtonName::D_PAD_RIGHT, 11);
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
				controller->setControlStick(100.0);
				controller->setCStick(100.0);
				controller->mapKey(Controller::ButtonName::A, 0);
				controller->mapKey(Controller::ButtonName::B, 2);
				controller->mapKey(Controller::ButtonName::X, 1);
				controller->mapKey(Controller::ButtonName::Y, 3);
				controller->mapKey(Controller::ButtonName::Z, 5);
				controller->mapKey(Controller::ButtonName::R, 4);
				controller->mapKey(Controller::ButtonName::L, 6);
				controller->mapKey(Controller::ButtonName::START, 7);
				controller->mapKey(Controller::ButtonName::D_PAD_UP, 8);
				controller->mapKey(Controller::ButtonName::D_PAD_LEFT, 9);
				controller->mapKey(Controller::ButtonName::D_PAD_DOWN, 10);
				controller->mapKey(Controller::ButtonName::D_PAD_RIGHT, 11);
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

// this is only getting the number of devices plugged in
// index of connected device might be greater than number of devices...
unsigned int SplashScreen::getConnectedDevices()
{
	int i = 0;
	while (sf::Joystick::isConnected(i))
	{
		i++;
	}
	return i;
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