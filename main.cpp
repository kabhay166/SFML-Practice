#include<SFML/Graphics.hpp>
#include "Game.h"

int main() {
	
	float dt;
	while (Game::instance()->isPlaying()) {

		dt = Game::instance()->m_clock.restart().asSeconds();
		Game::instance()->input();
		Game::instance()->update(dt);
		Game::instance()->draw();
	}


	return 0;
}