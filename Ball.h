#pragma once
#include<SFML/Graphics.hpp>

class Ball
{
public:
	Ball();
	Ball(float radius, sf::Color color, sf::Vector2f position, sf::Vector2f veclocity);
	sf::CircleShape getShape();
	void update(float dt);
	sf::Vector2f getPosition() const;
	float getRadius() const;
	sf::Vector2f getVelocity();
	void setVelocity(sf::Vector2f velocity);
	void setColor(sf::Color color);
	void setCollided(bool collided);
	sf::Color getColor() const;
	void setSlow();
	bool getHitPlayer1();
	bool getHitPlayer2();
	void setHitPlayer1(bool hitPlayer1);
	void setHitPlayer2(bool hitPlayer2);
	void setRadius(float radius);
	void setPosition(sf::Vector2f position);
	
private:
	bool m_HitPlayer1 = false;
	bool m_HitPlayer2 = false;
	float m_slowFactor = 1.0;
	bool m_collided = false;
	sf::CircleShape m_shape;
	sf::Vector2f m_position;
	sf::Vector2f m_velocity;
	float m_radius;
	sf::Color m_color;
};

