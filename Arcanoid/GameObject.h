#pragma once
#include "Physics.h"

class GameObject : public Physics
{
public:
	//virtual bool intersect(sf::Shape& shape) = 0;
	virtual sf::Shape& get_shape() = 0;
	virtual void update(bool contact=false) = 0;
};