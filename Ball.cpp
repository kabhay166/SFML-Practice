#include "Ball.h"
#include "Game.h"
#include <iostream>

Ball::Ball () {
	
}

Ball::Ball(float radius, sf::Color color, sf::Vector2f position,sf::Vector2f veclocity) {
	m_shape.setRadius(radius);
	m_shape.setFillColor(color);
	m_position = position;
	m_velocity = veclocity;
	m_radius = radius;
	m_color = color;
	m_shape.setOrigin(m_radius,m_radius);
	m_shape.setPosition(m_position);
}

void Ball::update(float dt) {


	
	
	///////// update the position vector //////////////

		m_position.x += m_velocity.x * dt / (m_slowFactor);
		m_position.y += m_velocity.y * dt / (m_slowFactor);
	
	//////////////////////////////////////////////////

	///////////////////// Reverse velocities if position goes out of bounds ///////////////////

		/*if (m_position.x < m_radius || m_position.x + m_radius > Game::m_WIDTH) {
			m_velocity.x *= -1;	
		}*/

		if (m_position.y < Game::startY +  m_radius || m_position.y + m_radius > Game::m_HEIGHT) {
			m_velocity.y *= -1;
		}

	//////////////////////////////////////////////////////////////////////////////////////////


	/////////////////////////////// Change the color of the player if it touches the walls ///////////////////////////////

	/*if ((m_position.x - m_radius >= 0 && m_position.x - m_radius <= 5) || 
		(m_position.x + m_radius >= Game::m_WIDTH - 5 && m_position.x + m_radius <= Game::m_WIDTH)) {

			m_shape.setFillColor(sf::Color::Blue);
	}
	else if ((m_position.y - m_radius >= 0 && m_position.y - m_radius <= 5) || 
		(m_position.y + m_radius >= Game::m_HEIGHT - 5 && m_position.x + m_radius <= Game::m_HEIGHT)) {

			m_shape.setFillColor(sf::Color::Blue);

	}
	else {

		m_shape.setFillColor(m_color);
	}*/

	///////////////////////////////////////////////////////////////////////////////////////////

	


	/*if (m_position.x < 0) {
		m_position.x = m_radius;
	}
	else if (m_velocity.x > Game::m_WIDTH) {
		m_position.x = Game::m_WIDTH - m_radius;
	}
	

	if (m_position.y < 0) {
		m_position.y = m_radius;
	}
	else if (m_velocity.y > Game::m_HEIGHT) {
		m_position.y = Game::m_HEIGHT - m_radius;
	}*/
	
	m_shape.setPosition(m_position);

	//m_collided = false;

	if (m_slowFactor > 1) {
		m_slowFactor -= 2.5*dt;
	}

	if (m_slowFactor < 1) {
		m_slowFactor = 1;
	}

}

sf::CircleShape Ball::getShape() {
	return m_shape;
}


sf::Vector2f Ball::getPosition() const {
	return m_position;
}

float Ball::getRadius() const {
	return m_radius;
}

sf::Vector2f Ball::getVelocity() {
	return m_velocity;
}

void Ball::setVelocity(sf::Vector2f velocity) {
	m_velocity = velocity;
}

void Ball::setColor(sf::Color color) {
	m_shape.setFillColor(color);
}

void Ball::setCollided(bool collided) {
	m_collided = collided;
}

sf::Color Ball::getColor() const {
	return m_shape.getFillColor();
}

void Ball::setSlow() {
	std::cout << "Slowing the ball\n";
	m_slowFactor = 5;
}


bool Ball::getHitPlayer1() {
	return m_HitPlayer1;
}

bool Ball::getHitPlayer2() {
	return m_HitPlayer2;
}

void Ball::setHitPlayer1(bool hitPlayer1) {
	m_HitPlayer1 = hitPlayer1;
}

void Ball::setHitPlayer2(bool hitPlayer2) {
	m_HitPlayer2 = hitPlayer2;
}

void Ball::setRadius(float radius) {
	m_shape.setRadius(radius);
}

void Ball::setPosition(sf::Vector2f position) {
	m_position = position;
}
