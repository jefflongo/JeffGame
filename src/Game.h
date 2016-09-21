#ifndef GAME_H_
#define GAME_H_

#include "SFML/Graphics.hpp"

class GameState;

class Game
{
public:
	Game();
	~Game();

	bool isRunning();
	void quit();

	void setState(GameState* state); // TODO: don't let states have access to the entire game object
	void handleEvents();
	void update();
	void render();

	void toggleDebug();
	bool getDebugMode() const;
	unsigned int getFramerate();
	void setFramerate(unsigned int targetFps);
	//void calculateFramerate();
	void lowerFramerate();
	void increaseFramerate();

private:
	sf::RenderWindow window_;
	GameState* state_ = nullptr;
	sf::Clock clock_;
	sf::Font font_;
	sf::Text fpsText_;
	sf::Event event_;
	const unsigned int MAX_UPDATES = 30;
	unsigned int targetFps_ = 60;
	bool running_ = true, debugMode_ = false;
	double frametime_ = 1000000. / targetFps_, remainingTime_ = 0;
};

#endif // GAME_H_