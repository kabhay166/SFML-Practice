#include "ScoreMessage.h"
#include <iostream>



ScoreMessage::ScoreMessage() {};

ScoreMessage::ScoreMessage(std::string text, sf::Vector2f position, sf::Vector2f velocity, sf::Color color) 
	: m_position(position), 
	m_velocity(velocity), 
	m_color(color) {
	
	
	if (!m_font.loadFromFile("fonts/Roboto.ttf")) {
		std::cout << "Error loading the font\n";
	};
	m_score.setFont(m_font);
	m_score.setCharacterSize(20);
	m_score.setString(text);
	m_score.setOrigin(m_score.getLocalBounds().getSize().x / 2, m_score.getLocalBounds().getSize().y / 2);
	m_score.setPosition(m_position);
	
}

void ScoreMessage::update(float dt) {
	
	m_lifeSpan -= m_decreaseLifeSpan * dt;
	float alpha = (m_lifeSpan / m_maxLifeSpan) * 255;
	alpha = std::max(0.0f, std::min(255.0f,alpha));
		m_color.a =  static_cast<sf::Uint8>(alpha);
	
	std::cout << (int)m_color.a << "\n";

	if (m_color.a <= 0.0f) {
		m_isAlive = false;
	}



	m_position.x += m_velocity.x*dt;
	m_position.y += m_velocity.y*dt;

	m_score.setPosition(m_position);
	m_score.setFillColor(m_color);


}


const sf::Text& ScoreMessage::getText() const  {
	return m_score;
}


bool ScoreMessage::getAlive() {
	return m_isAlive;
}