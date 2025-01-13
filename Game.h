#pragma once
#include<SFML/Graphics.hpp>
#include "Player.h"
#include "Ball.h"

class Game
{
public:
	sf::Clock m_clock;
	static Game* instance();
	void update(float dt);
	void draw();
	void input();
	bool isPlaying() const ;
	void HandleCollision();
	const static int m_WIDTH = 800;
	const static int m_HEIGHT = 600;
	void checkGameOver();

private:
	std::vector<Ball> m_balls;
	Game();
	~Game();
	static Game* m_game;
	sf::RenderWindow* m_window;
	bool m_isPlaying = true;
	bool m_pause = false;
	Ball m_ball;
	Player m_player1;
	Player m_player2;
	sf::Event m_event;
	
};

