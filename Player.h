#pragma once
#include<SFML/Graphics.hpp>


class Player
{

public:

	Player();
	Player(sf::Vector2f size, sf::Color color, sf::Vector2f position);
	sf::RectangleShape getShape();
	void update(float dt);
	void setMoveUp(bool moveUp);
	void setMoveDown(bool moveDown);
	sf::Vector2f getPosition();
	sf::Vector2f getVelocity();
	sf::Vector2f getSize() const;
	sf::Color getColor() const;
	bool usePowerDouble();
	bool usePowerSlow();
	bool usePowerElongate();
	void setUsePowerDouble();
	void setUsePowerSlow();
	void setUsePowerElongate();
	bool getUsePowerDouble();
	bool getUsePowerSlow();
	bool getUsePowerElongate();
	void setAllPowerFalse();
	void accelerate();
	void decelerate();
	void setPosition(sf::Vector2f position);

private:
	float m_acceleration = 500.0;
	bool m_accelerate = false;
	bool m_decelerate = false;
	bool m_usePowerDouble = false;
	bool m_usePowerSlow = false;
	bool m_usePowerElongate = false;
	int m_powerDouble = 1;
	int m_powerSlow = 1;
	int m_powerElongate = 1;
	bool m_moveUp = false;
	bool m_moveDown = false;
	sf::RectangleShape m_shape;
	sf::Vector2f m_position;
	sf::Vector2f m_size;
	sf::Vector2f m_velocity;
	sf::Color m_color;
	
};

