#include "BallTrail.h"
#include<iostream>




BallTrail::BallTrail(Ball& ball) : m_ball(ball)
{
	
	for (int i = 0; i < 3; i++) {
		
		m_ballTrail[i].setRadius(m_ball.getRadius());
		m_ballTrail[i].getShape().setOrigin(m_ballTrail[i].getRadius(), m_ballTrail[i].getRadius());
		m_ballTrail[i].setPosition(m_ball.getPosition());
	}
}

BallTrail::~BallTrail(){
}

Ball* BallTrail::getBalls() {
	return m_ballTrail;
}

void BallTrail::update(float dt) {

	

	for (int i = 0; i < 3; i++) {

		float x = m_ball.getPosition().x  - m_ball.getVelocity().x* 2*(i+100) * dt;
		float y = m_ball.getPosition().y  + m_ball.getVelocity().y* 2*(i+200) * dt;

		m_ballTrail[i].setPosition(sf::Vector2f(x, y));
		m_ballTrail[i].setVelocity(m_ball.getVelocity());
		sf::Color color = m_ball.getColor();
		m_ballTrail[i].setColor(sf::Color(color.r,color.g,(int)color.b,10 + 10*i));

		m_ballTrail[i].update(dt);
		
	}



	
}

void BallTrail::draw(sf::RenderWindow* window) {
	for (int i = 0; i < 3; i++) {
		window->draw(m_ballTrail[i].getShape());
	}
}
