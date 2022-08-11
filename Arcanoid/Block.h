#pragma once
#include "GameObject.h"

class Block : public GameObject
{
private:
	sf::RectangleShape shape;
	size_t lifes;
	std::map<int, sf::Color> ColorsMap
	{
		{0, sf::Color(0, 0, 0)},
		{1, sf::Color(255, 0, 0)},
		{2, sf::Color(255, 127, 0)},
		{3, sf::Color(255, 255, 0)},
		{4, sf::Color(127, 255, 0)},
		{5, sf::Color(0, 255, 0)},
		{6, sf::Color(0, 255, 127)},
		{7, sf::Color(0, 255, 255)},
		{8, sf::Color(0, 127, 255)},
		{9, sf::Color(0, 0, 255)},
		{10, sf::Color(127, 0, 255)},
		{11, sf::Color(255, 0, 255)}
	};

public:
	Block(float x, float y, size_t lifes, size_t w=300, size_t h=150, sf::Texture* texture=nullptr)
	{
		shape.setPosition(x, y);
		shape.setSize(sf::Vector2f(w, h));
		if (texture != nullptr)
		{
			shape.setTexture(texture);
		}
		Block::lifes = lifes;
		shape.setFillColor(ColorsMap[lifes]);
	}

	// Унаследовано через GameObject
	virtual void init_object() override {};
	virtual float get_velocity() override { return 0; };
	virtual void set_velocity(float dr) override {};
	virtual sf::Shape& get_shape() override { return shape; };
	virtual void update(bool contact = false) 
	{
		if (contact)
		{
			lifes--;
			if (lifes > 0) shape.setFillColor(ColorsMap[lifes]);
			if (lifes == 0) shape.~RectangleShape();
		}
	};
};

