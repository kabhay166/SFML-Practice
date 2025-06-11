#pragma once
#include <SFML/Graphics.hpp>
#include <string>

class ScoreMessage
{

public:
	ScoreMessage();
	ScoreMessage(std::string text, sf::Vector2f position, sf::Vector2f velocity, sf::Color color);
	void update(float dt);
	const sf::Text& getText() const;
	bool getAlive();

private:
	sf::Vector2f m_position;
	float lifeDuration = 0.7;
	sf::Text m_score;
	sf::Font m_font;
	float m_lifeSpan = 100.0f;
	float m_maxLifeSpan = 100.0f;
	float m_decreaseLifeSpan = 100.0f/lifeDuration;
	sf::Vector2f m_velocity = sf::Vector2f(1.5,-10);
	sf::Color m_color;
	bool m_isAlive = true;
};

