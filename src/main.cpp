// Jeff Longo
// 09/19/16

#include "Game.h"
#include "gamestates/SplashScreen.h"

int main()
{
	Game game;
	game.setState(new SplashScreen());

	while (game.isRunning())
	{
		game.handleEvents();
		game.update();
		game.render();
	}
	return 0;
}