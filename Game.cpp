#include "Game.h"
#include<iostream>


Game* Game::m_game = nullptr;

Game::Game() {
	m_window = new sf::RenderWindow(sf::VideoMode(m_WIDTH, m_HEIGHT), "SFML Practice");
	m_event = sf::Event();
	Ball ball = Ball(8,sf::Color::Green,sf::Vector2f(50,50), sf::Vector2f(300, 200));
	m_balls.push_back(ball);
	
	m_player1 = Player(sf::Vector2f(15, 50), sf::Color::Red, sf::Vector2f(7.5, Game::m_HEIGHT / 2));
	m_player2 = Player(sf::Vector2f(15, 50), sf::Color::Yellow, sf::Vector2f(Game::m_WIDTH -  7.5, Game::m_HEIGHT / 2));

}

Game::~Game() {
	delete m_window;
}

Game* Game::instance() {
	if (m_game == nullptr) {
		m_game = new Game();
	}

	return m_game;
}

bool Game::isPlaying() const {
	return m_isPlaying;
}


void Game::input() {
	while (m_window->pollEvent(m_event)) {
		if (m_event.type == sf::Event::Closed) {
			m_isPlaying = false;
			m_window->close();
		}


		
		if (m_event.type == sf::Event::KeyPressed) {
			if (m_event.key.code == sf::Keyboard::Enter) {
				m_pause = !m_pause;
			}
		}

		//////////////////////////// Controls for player 1 ////////////////////////////
		if (m_event.type == sf::Event::KeyReleased) {
			if (m_event.key.code == sf::Keyboard::W) {
				m_player1.setMoveUp(false);
			}

			if (m_event.key.code == sf::Keyboard::S) {
				m_player1.setMoveDown(false);
			}
		}

		if (sf::Keyboard::isKeyPressed(sf::Keyboard::W)) {
			m_player1.setMoveUp(true);
		}

		

		if (sf::Keyboard::isKeyPressed(sf::Keyboard::S)) {
			m_player1.setMoveDown(true);
		}

		///////////////////////////////////////////////////////////////////////////////////////////////////
		
		

		
		//////////////////////////// Controls for player 2 ////////////////////////////
		if (m_event.type == sf::Event::KeyReleased) {
			if (m_event.key.code == sf::Keyboard::Up) {
				m_player2.setMoveUp(false);
			}

			if (m_event.key.code == sf::Keyboard::Down) {
				m_player2.setMoveDown(false);
			}
		}

		if (sf::Keyboard::isKeyPressed(sf::Keyboard::Up)) {
			m_player2.setMoveUp(true);
		}



		if (sf::Keyboard::isKeyPressed(sf::Keyboard::Down)) {
			m_player2.setMoveDown(true);
		}
		///////////////////////////////////////////////////////////////////////////////


		
		
	}
}


void Game::checkGameOver() {
	if (m_ball.getPosition().x < 0 || m_ball.getPosition().x > Game::m_WIDTH) {
		m_pause = true;
	}
}

void Game::draw() {
	m_window->clear(sf::Color::Black);
	m_window->draw(m_player1.getShape());
	m_window->draw(m_player2.getShape());

	for (auto& ball : m_balls) {
		m_window->draw(ball.getShape());

	}
	m_window->display();
}

void Game::update(float dt) {

	if (!m_pause) {
		HandleCollision();
		m_player1.update(dt);
		m_player2.update(dt);
		for (auto& ball : m_balls) {
			ball.update(dt);

		}
		checkGameOver();
	}
}

void Game::HandleCollision() {

	for (auto& ball : m_balls) {
		if (ball.getPosition().x <= Game::m_WIDTH / 4 || ball.getPosition().x >= 3 * Game::m_WIDTH / 4) {



			////////////////////////////////// Check Collision with player 1 //////////////////////////////////////////////////

			if (ball.getPosition().y + ball.getRadius() >= m_player1.getPosition().y - m_player1.getSize().y / 2 &&
				ball.getPosition().y - ball.getRadius() <= m_player1.getPosition().y + m_player1.getSize().y / 2) {



				if (ball.getPosition().x - ball.getRadius() >= 0 && ball.getPosition().x - ball.getRadius() <= m_player1.getPosition().x + m_player1.getSize().x / 2) {

					sf::Vector2f velocity = sf::Vector2f(-ball.getVelocity().x * 1.1, ball.getVelocity().y * 1.1);
					ball.setVelocity(velocity);
					ball.setColor(m_player1.getColor());

				}

			}

			///////////////////////////////////////////////////////////////////////////////////////////////////////////////////


			////////////////////////////////// Check Collision with player 2 //////////////////////////////////////////////////

			if (ball.getPosition().y + ball.getRadius() >= m_player2.getPosition().y - m_player2.getSize().y / 2 &&
				ball.getPosition().y - ball.getRadius() <= m_player2.getPosition().y + m_player2.getSize().y / 2) {



				if (ball.getPosition().x + ball.getRadius() >= Game::m_WIDTH - m_player2.getSize().x / 2 && ball.getPosition().x + ball.getRadius() <= Game::m_WIDTH) {

					sf::Vector2f velocity = sf::Vector2f(-ball.getVelocity().x, ball.getVelocity().y);
					ball.setVelocity(velocity);
					ball.setColor(m_player2.getColor());


				}

			}

	}

	
			//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
		
	}
}

