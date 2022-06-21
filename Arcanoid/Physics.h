#pragma once

class Physics
{
protected:
	sf::Vector2f v{0, 0};
	float angle = 0;
	virtual void init_object() = 0;

public:
	virtual float get_velocity() = 0;
	virtual void set_velocity(float dr) = 0;
};

