#pragma once
#include<SFML/Graphics.hpp>
#include "Player.h"
#include "Ball.h"
#include "BallTrail.h"
#include "ScoreMessage.h"


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
	const static int m_HEIGHT = 800;
	const static int startY = 200;
	void checkGameOver();
	void reset();
	 


private:
	
	Game();
	~Game();
	std::vector<Ball> m_balls;
	static Game* m_game;
	sf::RenderWindow* m_window;
	bool m_isPlaying = true;
	bool m_pause = false;
	bool m_gameOver = false;
	Player m_player1;
	Player m_player2;
	sf::Event m_event;
	int m_scorePlayer1 = 0;
	int m_scorePlayer2 = 0;
	int m_points = 10;
	sf::Font m_font;
	sf::Text m_scoreText;
	sf::Text m_scoreTextPlayer1;
	sf::Text m_scoreTextPlayer2;
	sf::RectangleShape m_gameArea;
	ScoreMessage* m_scoreMessage = nullptr;
	
	

	
	
};

