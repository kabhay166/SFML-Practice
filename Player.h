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
	sf::Vector2f getSize() const;
	sf::Color getColor() const;
	bool usePowerDouble();
	bool usePowerSlow();
private:

	int m_powerDouble = 1;
	int m_powerSlow = 1;
	bool m_moveUp = false;
	bool m_moveDown = false;
	sf::RectangleShape m_shape;
	sf::Vector2f m_position;
	sf::Vector2f m_size;
	sf::Vector2f m_velocity;
	sf::Color m_color;
	
};

