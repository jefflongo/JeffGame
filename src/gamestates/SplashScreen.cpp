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
	static bool startPressed = false;
	static unsigned int controllerId;
	static Controller::Controls controls;
	static Controller* controller = nullptr; // TODO: when do we delete this??
	static int fadeTimer = 100;

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
				controllerId = i;
				controls =
				{
					80.0, 50.0, -100.0, 60.0,
					{ 0, true },{ 1, true },{ 2, true },{ 3, true },{ 4, true },{ 5, true },{ 6, true },{ 7, true },{ 8, true },{ 9, true },{ 10, true },{ 11, true }
				};
				controller = new Controller(controllerId, controls);
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
				controllerId = i;
				controls =
				{
					100.0, 100.0, 0.0, 100.0,
					{ 0, true },{ 2, true },{ 1, true },{ 3, true },{ 5, true },{ 4, true },{ 6, true },{ 7, true },{ 8, true },{ 9, true },{ 10, true },{ 11, true }
				};
				controller = new Controller(controllerId, controls);
				startPressed = true;
				break;
			}
		}
	}
	if (startPressed)
	{
		static int vol = 100;
		if (--vol > 0)
		{
			theme_.setVolume(static_cast<float>(vol));
		}
		if (fadeTimer == 0)
		{
			game.setState(new Battle(controller));
		}
		fadeTimer--;
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