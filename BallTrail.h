#pragma once
#include "Ball.h"

class BallTrail
{

public:
	BallTrail(Ball& ball);
	~BallTrail();
	Ball* getBalls();
	void update(float dt);
	void draw(sf::RenderWindow* window);

private:
	Ball& m_ball;
	Ball m_ballTrail[3];
};

