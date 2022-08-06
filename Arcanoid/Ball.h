#pragma once
#include "GameObject.h"
#include "RandomGenerator.h"

class Ball : public GameObject
{
public:
	sf::CircleShape shape;
	float radius, win_w, win_h;

	Ball(float x, float y, float w_w, float w_h, float size=10, sf::Color color=sf::Color::Red)
	{
		win_w = w_w;
		win_h = w_h;
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
		sf::Vector2f tmp_v = shape.getPosition();
		if ((tmp_v.x - radius <= 0) || (tmp_v.x + radius >= win_w)) v.x = -v.x;
		if ((tmp_v.y - radius <= 0) || (tmp_v.y + radius >= win_h)) v.y = -v.y;
		shape.move(v);
	}
};
