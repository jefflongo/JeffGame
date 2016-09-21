#include "Game.h"

#include "Globals.h"
#include "GameState.h"

Game::Game()
	: window_(sf::VideoMode(Globals::WINDOW_WIDTH, Globals::WINDOW_HEIGHT), "The Fox Ditto v1.4", sf::Style::Default)
{
	window_.setKeyRepeatEnabled(false);
	font_.loadFromFile("res/fonts/PressStart2P.ttf");
	fpsText_.setFont(font_);
	fpsText_.setPosition(sf::Vector2f(Globals::WINDOW_WIDTH - 100, 20));
}

Game::~Game()
{
	if (state_ != nullptr)
	{
		state_->destroy();
		delete state_;
	}
}

void Game::setState(GameState* state)
{
	if (state_ != nullptr)
	{
		state_->destroy();
		delete state_;
	}
	state_ = state;
	if (state_ != nullptr)
	{
		state_->init();
	}
}

void Game::update()
{
	unsigned int updates = 0;
	remainingTime_ += clock_.restart().asMicroseconds();
	while (remainingTime_ >= frametime_)
	{
		remainingTime_ -= frametime_;
		if (updates++ < MAX_UPDATES)
		{
			state_->update(*this);
		}
		/*
		if (debugMode_)
		{
		calculateFramerate();
		}
		*/
	}
}

bool Game::isRunning()
{
	return running_;
}

void Game::quit()
{
	running_ = false;
}

void Game::handleEvents()
{
	while (window_.pollEvent(event_))
	{
		if (event_.type == sf::Event::EventType::Closed)
		{
			window_.close();
		}
		if (event_.type == sf::Event::KeyPressed)
		{
			switch (event_.key.code)
			{
			case sf::Keyboard::Escape:
				window_.close();
				break;
			case sf::Keyboard::F1:
				toggleDebug();
				if (!debugMode_ && targetFps_ != 60)
				{
					setFramerate(60);
				}
				break;
			case sf::Keyboard::F2:
				if (debugMode_)
				{
					lowerFramerate();
				}
				break;
			case sf::Keyboard::F3:
				if (debugMode_)
				{
					increaseFramerate();
				}
				break;
			}
		}
	}
}

void Game::render()
{
	window_.clear(sf::Color::Black);
	state_->render(window_);
	if (debugMode_)
	{
		window_.draw(fpsText_);
	}
	window_.display();
}

void Game::toggleDebug()
{
	debugMode_ = !debugMode_;
}

bool Game::getDebugMode() const
{
	return debugMode_;
}

unsigned int Game::getFramerate()
{
	return targetFps_;
}

void Game::setFramerate(unsigned int value)
{
	targetFps_ = value;
	frametime_ = 1000000.f / targetFps_;
}

/*
void Game::calculateFramerate()
{
	// Add 0.5 to round to the nearest integer with truncation
	std::string onScreenFps = Globals::intToStr(static_cast<unsigned int>(1000000. / (frametime_)+0.5));
	fpsText_.setString(onScreenFps);
}
*/

void Game::lowerFramerate()
{
	if (targetFps_ == 240)
	{
		setFramerate(120);
	}
	else if (targetFps_ == 120)
	{
		setFramerate(60);
	}
	else if (targetFps_ == 60)
	{
		setFramerate(30);
	}
	else if (targetFps_ == 30)
	{
		setFramerate(15);
	}
	else if (targetFps_ == 15)
	{
		setFramerate(5);
	}
	else if (targetFps_ == 5)
	{
		setFramerate(1);
	}
	else if (targetFps_ == 1)
	{

	}
	else
	{
		setFramerate(60);
	}
}

void Game::increaseFramerate()
{
	if (targetFps_ == 1)
	{
		setFramerate(5);
	}
	else if (targetFps_ == 5)
	{
		setFramerate(15);
	}
	else if (targetFps_ == 15)
	{
		setFramerate(30);
	}
	else if (targetFps_ == 30)
	{
		setFramerate(60);
	}
	else if (targetFps_ == 60)
	{
		setFramerate(120);
	}
	else if (targetFps_ == 120)
	{
		setFramerate(240);
	}
	else if (targetFps_ == 240)
	{

	}
	else
	{
		setFramerate(60);
	}
}