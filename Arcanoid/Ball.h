#pragma once
#include "GameObject.h"
#include "RandomGenerator.h"

class Ball : public GameObject
{
public:
	sf::CircleShape shape;
	float radius;

	Ball(float x, float y, float size=10, sf::Color color=sf::Color::Red)
	{
		radius = size / 2;
		shape.setPosition(x, y);
		shape.setRadius(size);
		shape.setFillColor(color);
		shape.setOrigin(radius, radius);
		init_object();
	}

	virtual sf::Shape& get_shape() override
	{
		return shape;
	}

	virtual float get_velocity()
	{
		return 0;
	}

	virtual void set_velocity(float dr) override
	{
		v.x = dr * cos(angle);
		v.y = dr * sin(angle);
	}

	virtual void init_object() override
	{
		RandomGenerator<float> rx(-1.5, 1.5), ry(-2, -1);
		v.y = ry.get_float();
		v.x = rx.get_float();
		angle = v.y / v.x;
	}

	virtual void update() override
	{
		shape.move(v);
	}
};

