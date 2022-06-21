#pragma once
#include "GameObject.h"

class Ball : public GameObject
{
public:
	sf::CircleShape shape;
	double radius;

	Ball(double x, double y, double size=10, sf::Color color=sf::Color::Red)
	{
		radius = size / 2;
		shape.setPosition(x, y);
		shape.setRadius(size);
		shape.setFillColor(color);
		shape.setOrigin(radius, radius);
	}

	virtual sf::Shape& get_shape() override
	{
		return shape;
	}

	virtual double get_velocity()
	{
		return 0;
	}
};

