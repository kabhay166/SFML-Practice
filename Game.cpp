#include "Game.h"
#include<iostream>
#include <random>
#include <string>

Game* Game::m_game = nullptr;

Game::Game() {
	m_window = new sf::RenderWindow(sf::VideoMode(m_WIDTH, m_HEIGHT), "SFML Practice");
	m_event = sf::Event();
	
	reset();

	m_font.loadFromFile("fonts/Roboto.ttf");

	//////////// Initializing scoreText ///////////////
	m_scoreText.setFont(m_font);
	m_scoreText.setCharacterSize(70);
	m_scoreText.setString("Scores");
	m_scoreText.setOrigin(m_scoreText.getLocalBounds().getSize().x / 2, m_scoreText.getLocalBounds().getSize().y / 2);
	m_scoreText.setPosition(Game::m_WIDTH/2, 40);
	m_scoreText.setFillColor(sf::Color::White);

	/////////// Initializing Player 1 score //////////////
	m_scoreTextPlayer1.setFont(m_font);
	m_scoreTextPlayer1.setCharacterSize(30);
	m_scoreTextPlayer1.setString("Player 1: " + std::to_string(m_scorePlayer1));
	m_scoreTextPlayer1.setPosition(20, 100);
	m_scoreTextPlayer1.setFillColor(sf::Color::White);

	/////////// Initializing Player 2 score //////////////
	m_scoreTextPlayer2.setFont(m_font);
	m_scoreTextPlayer2.setCharacterSize(30);
	m_scoreTextPlayer2.setString("Player 2: " + std::to_string(m_scorePlayer2));
	m_scoreTextPlayer2.setPosition(Game::m_WIDTH - m_scoreTextPlayer2.getLocalBounds().getSize().x - 20, 100);
	m_scoreTextPlayer2.setFillColor(sf::Color::White);

	////////// Initialize the game area //////////////
	m_gameArea.setPosition(0, 200);
	m_gameArea.setSize(sf::Vector2f(Game::m_WIDTH, Game::m_HEIGHT - 200));
	m_gameArea.setFillColor(sf::Color(120,130,140,100));
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

				if (m_gameOver) {
					
					reset();
				}
				else {
					m_pause = !m_pause;
				
				}
			}

		}


		//////////////////////////// Controls for player 1 ////////////////////////////




			////////////////////////////// Movement Controls ///////////////////////////

				if (m_event.type == sf::Event::KeyReleased) {
					if (m_event.key.code == sf::Keyboard::W) {
						m_player1.setMoveUp(false);
						m_player1.decelerate();
					}

					if (m_event.key.code == sf::Keyboard::S) {
						m_player1.setMoveDown(false);
						m_player1.decelerate();
					}
				}

				if (sf::Keyboard::isKeyPressed(sf::Keyboard::W)) {
					m_player1.setMoveUp(true);
					m_player1.accelerate();
				}

		

				if (sf::Keyboard::isKeyPressed(sf::Keyboard::S)) {
					m_player1.setMoveDown(true);
					m_player1.accelerate();
				}

			/////////////////////////////////////////////////////////////////////////////



			//////////////////////////// Power Controls ///////////////////////////

				if (m_event.type == sf::Event::KeyPressed) {

					if (m_event.key.code == sf::Keyboard::D) {
						m_player1.setUsePowerDouble();
					}

					if (m_event.key.code == sf::Keyboard::F) {
						m_player1.setUsePowerSlow();
						if (m_player1.usePowerSlow()) {
							for (auto& ball : m_balls) {
								ball.setSlow();
							}
						}
					}
				}

				

			///////////////////////////////////////////////////////////////////////



		///////////////////////////////////////////////////////////////////////////////////////////////////
		
		

		
		//////////////////////////// Controls for player 2 ////////////////////////////


			if (m_event.type == sf::Event::KeyReleased) {
				if (m_event.key.code == sf::Keyboard::Up) {
					m_player2.setMoveUp(false);
					m_player2.decelerate();
				}

				if (m_event.key.code == sf::Keyboard::Down) {
					m_player2.setMoveDown(false);
					m_player2.decelerate();
				}
			}

			if (sf::Keyboard::isKeyPressed(sf::Keyboard::Up)) {
				m_player2.setMoveUp(true);
				m_player2.accelerate();
			}



			if (sf::Keyboard::isKeyPressed(sf::Keyboard::Down)) {
				m_player2.setMoveDown(true);
				m_player2.accelerate();
			}


		///////////////////////////////////////////////////////////////////////////////


		
		
	}
}


void Game::checkGameOver() {
	for (auto& ball : m_balls) {
		if (ball.getPosition().x < 0 || ball.getPosition().x > Game::m_WIDTH) {
			m_pause = true;
			m_gameOver = true;
		}
	}
	
}

void Game::draw() {
	m_window->clear(sf::Color::Black);
	m_window->draw(m_scoreText);
	m_window->draw(m_scoreTextPlayer1);
	m_window->draw(m_scoreTextPlayer2);
	m_window->draw(m_gameArea);
	m_window->draw(m_player1.getShape());
	m_window->draw(m_player2.getShape());

	for (auto& ball : m_balls) {
		m_window->draw(ball.getShape());

	}

	/*for (auto& scoreMessage : m_scoreMessages) {
		if (scoreMessage.getAlive()) {
			m_window->draw(scoreMessage.getText());
		}
	}*/

	if (m_scoreMessage != nullptr){

		m_window->draw(m_scoreMessage->getText());
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

		if (m_scoreMessage != nullptr) {

			m_scoreMessage->update(dt);
		}

		

		std::string scoreText = "";
		scoreText = "Player 1: " + std::to_string(m_scorePlayer1);
		m_scoreTextPlayer1.setString(scoreText);

		scoreText = "Player 2: " + std::to_string(m_scorePlayer2);
		m_scoreTextPlayer2.setString(scoreText);

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



					if (!ball.getHitPlayer1() ) {

						/////////// Change the hit state of ball for both players ////////////
						ball.setHitPlayer1(true);
						ball.setHitPlayer2(false);
						/////////////////////////////////////////////////////////////////////



						/////////////// create the score message  and add player points  /////////////////
						
						sf::Vector2f scoreVelocity = sf::Vector2f(100, -m_player1.getVelocity().y);
						m_scoreMessage = new ScoreMessage(std::string("+10"), m_player1.getPosition(), scoreVelocity, m_player1.getColor());
						m_scorePlayer1 += m_points;

						/////////////////////////////////////////////////////////////////////////////////
						

						///////////////////// Change the ball's velocity and color ///////////////////////////////
						
						sf::Vector2f ballVelocity = sf::Vector2f(-ball.getVelocity().x * 1.02, ball.getVelocity().y * 1.02);
						ball.setVelocity(ballVelocity);
						ball.setColor(m_player1.getColor());
						
						////////////////////////////////////////////////////////////////////////////////////////


						///////////////////// Check if player is using any powers /////////////////////


						if (m_player1.getUsePowerDouble()) {


							if (m_player1.usePowerDouble()) {
								Ball new_ball = Ball(ball.getRadius(), ball.getColor(), ball.getPosition(), sf::Vector2f(ball.getVelocity().x + 1, ball.getVelocity().y + 2));
								new_ball.setHitPlayer1(ball.getHitPlayer1());
								new_ball.setHitPlayer2(ball.getHitPlayer2());
								m_balls.push_back(new_ball);
							}
							else {
								std::cout << "Can't use this power\n";
							}



						}

						///////////////////////////////////////////////////////////////////////////////

						


					}

		

					/*if (m_player1.getUsePowerSlow()) {
						if (m_player1.usePowerSlow()) {
							ball.setSlow();
						}
					}*/

				}

			}

			///////////////////////////////////////////////////////////////////////////////////////////////////////////////////


			////////////////////////////////// Check Collision with player 2 //////////////////////////////////////////////////

			if (ball.getPosition().y + ball.getRadius() >= m_player2.getPosition().y - m_player2.getSize().y / 2 &&
				ball.getPosition().y - ball.getRadius() <= m_player2.getPosition().y + m_player2.getSize().y / 2) {


				if (ball.getPosition().x + ball.getRadius() >= Game::m_WIDTH - m_player2.getSize().x / 2 && ball.getPosition().x + ball.getRadius() <= Game::m_WIDTH) {


					if (!ball.getHitPlayer2()) {


						///////////// Change the hit state of ball for both players ////////////

							ball.setHitPlayer2(true);
							ball.setHitPlayer1(false);
						
						///////////////////////////////////////////////////////////////////////
					
						/////////////// create the score message  and add player points  /////////////////
							
							sf::Vector2f scoreVelocity = sf::Vector2f(-100, -m_player1.getVelocity().y);
							m_scoreMessage = new ScoreMessage(std::string("+10"), m_player2.getPosition(), scoreVelocity, m_player2.getColor());
							m_scorePlayer2 += m_points;
						
						/////////////////////////////////////////////////////////////////////////////////


						///////////////////// Change the ball's velocity and color ///////////////////////////////
							
							sf::Vector2f ballVelocity = sf::Vector2f(-ball.getVelocity().x * 1.02, ball.getVelocity().y * 1.02);
							ball.setVelocity(ballVelocity);
							ball.setColor(m_player2.getColor());
						
						//////////////////////////////////////////////////////////////////////////////////////////
						
					}
					


				}

			}

	}

	
			//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
		
	}
}

void Game::reset() {

	m_gameOver = false;
	m_pause = false;
	
	//////////// for position randomness ///////////
	srand(time(NULL));

	float y = 200.0 + rand() % (Game::m_HEIGHT / 2);
	////////////////////////////////////////////////

	/////////// for velocity randomness ////////////
	srand(time(NULL));
	float vx = 200 + rand() % 100;

	srand(time(NULL));
	float vy = 250 + rand() % 50;

	m_balls.clear();
	Ball ball = Ball(8, sf::Color::Green, sf::Vector2f(Game::m_WIDTH / 2.0, y), sf::Vector2f(vx, vy));
	m_balls.push_back(ball);

	m_player1 = Player(sf::Vector2f(15, 50), sf::Color::Red, sf::Vector2f(7.5, Game::m_HEIGHT / 2));
	m_player2 = Player(sf::Vector2f(15, 50), sf::Color::Yellow, sf::Vector2f(Game::m_WIDTH - 7.5, Game::m_HEIGHT / 2));
	
}
