#pragma once

class Physics
{
protected:
	sf::Vector2f v{0, 0};
	virtual void init_object() = 0;

public:
	virtual ~Physics() = default;
	virtual float get_velocity() = 0;
	virtual void set_velocity(float dr) = 0;
	void inverse_x() { v.x = -v.x; }
	void inverse_y() { v.y = -v.y; }
};

