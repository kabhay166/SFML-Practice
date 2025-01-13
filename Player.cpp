#include "Player.h"
#include "Game.h"

Player::Player() {

}

Player::Player(sf::Vector2f size, sf::Color color, sf::Vector2f position) {
	m_size = size;
	m_color = color;
	m_position = position;
	m_velocity = sf::Vector2f(0,500);
	m_shape.setSize(m_size);
	m_shape.setFillColor(m_color);
	m_shape.setOrigin(m_size.x / 2, m_size.y / 2);
}

void Player::update(float dt) {
	
	if (m_position.y >= m_size.y/2 ) {
		
		if (m_moveUp) {
			float yIncrement = m_velocity.y * dt;
			m_position.y -= yIncrement;

		}
	}

	if (m_position.y + m_size.y/2 <= Game::m_HEIGHT) {
		if (m_moveDown) {
			float yIncrement = m_velocity.y * dt;
			m_position.y += yIncrement;
		}
	}

	m_shape.setPosition(m_position);

}

sf::RectangleShape Player::getShape() {
	return m_shape;
}


void Player::setMoveUp(bool moveUp) {
	m_moveUp = moveUp;
}

void Player::setMoveDown(bool moveDown) {
	m_moveDown = moveDown;
}

sf::Vector2f Player::getPosition() {
	return m_position;
}

sf::Vector2f Player::getSize() const {
	return m_size;
}

sf::Color Player::getColor() const {
	return m_shape.getFillColor();
}

bool Player::usePowerDouble() {
	if (m_powerDouble) {
		m_powerDouble--;
		return true;

	}
	else {
		return false;
	}
}

bool usePowerSlow() {

}