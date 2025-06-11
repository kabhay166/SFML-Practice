#include "Player.h"
#include "Game.h"
#include <iostream>

Player::Player() {

}

Player::Player(sf::Vector2f size, sf::Color color, sf::Vector2f position) {
	m_size = size;
	m_color = color;
	m_position = position;
	m_velocity = sf::Vector2f(0,0);
	m_shape.setSize(m_size);
	m_shape.setFillColor(m_color);
	m_shape.setOrigin(m_size.x / 2, m_size.y / 2);
}

void Player::update(float dt) {

	if (m_moveUp) {

		if (m_position.y > Game::startY +  m_size.y / 2) {
			//m_velocity.y -= m_acceleration*dt;
			m_position.y -= m_acceleration * dt;

		}
	}

	if (m_moveDown) {

		if (m_position.y < Game::m_HEIGHT - m_size.y / 2) {
			//m_velocity.y += m_acceleration* dt;
			m_position.y += m_acceleration * dt;

		}
	}

	if (m_decelerate) {
		if (m_velocity.y > 0.00001 || m_velocity.y < 0.0001) {
			if (m_velocity.y > 0) {
				m_velocity.y -= m_acceleration * 2 * dt;
			}
			else if (m_velocity.y < 0) {
				m_velocity.y += m_acceleration * 2 * dt;
			}

		}
		else {
			m_decelerate = false;

		}

	}
	
	//m_position.y += m_velocity.y * dt;

	if (m_position.y <= Game::startY) {
		m_position.y = m_size.y/2;
		m_velocity.y = 0;
		m_accelerate = false;
	}
	else if (m_position.y >= Game::m_HEIGHT) {
		m_position.y = Game::m_HEIGHT - m_size.y/2;
		m_velocity.y = 0;
		m_accelerate = false;
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

sf::Vector2f Player::getVelocity() {
	return m_velocity;
}

sf::Vector2f Player::getSize() const {
	return m_size;
}

sf::Color Player::getColor() const {
	return m_shape.getFillColor();
}

bool Player::usePowerDouble() {


	setAllPowerFalse();

	if (m_powerDouble) {
		m_powerDouble--;
		return true;

	}
	else {
		return false;
	}
}

bool Player::usePowerSlow() {
	if (m_usePowerSlow && m_powerSlow) {
		m_powerSlow--;
		setAllPowerFalse();
		return true;

	}
	else {
		return false;
	}
}

bool Player::usePowerElongate() {
	if (m_usePowerElongate && m_powerElongate) {
		m_powerElongate--;
		setAllPowerFalse();
		return true;

	}
	else {
		return false;
	}
}

void Player::setUsePowerDouble() {
	std::cout << "Power Double Activated\n";
	setAllPowerFalse();
	m_usePowerDouble = true;
	
}

void Player::setUsePowerSlow () {

	std::cout << "Power Slow Activated\n";
	setAllPowerFalse();
	m_usePowerSlow = true;
}

void Player::setUsePowerElongate() {
	std::cout << "Power Elongate Activated\n";
	setAllPowerFalse();
	m_usePowerElongate = true;
}

bool Player::getUsePowerDouble() {
	return m_usePowerDouble && m_powerDouble;
}

bool Player::getUsePowerSlow() {
	return m_usePowerSlow && m_powerSlow;
}

bool Player::getUsePowerElongate() {
	return m_usePowerElongate && m_powerElongate;
}

void Player::setAllPowerFalse() {
	m_usePowerDouble = false;
	m_usePowerSlow = false;
	m_usePowerElongate = false;
}


void Player::accelerate() {
	m_accelerate = true;
	m_decelerate = false;
}

void Player::decelerate() {
	m_accelerate = false;
	m_decelerate = true;
}

void Player::setPosition(sf::Vector2f position) {
	m_position = position;
}