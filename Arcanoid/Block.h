#pragma once

class Block : public GameObject
{
private:
	sf::RectangleShape shape;
	size_t lifes;
	size_t bonus;
	sf::Vector2f b_pos;
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
		{11, sf::Color(255, 0, 255)},
		{12, sf::Color(112, 128, 144)}
	};

public:
	Block(float x, float y, size_t lifes, size_t w=300, size_t h=150, sf::Texture* texture=nullptr, size_t bonus=0)
	{
		Block::bonus = bonus;
		shape.setPosition(x, y);
		shape.setSize(sf::Vector2f(w, h));
		Block::lifes = lifes;
		if (texture != nullptr)
			shape.setTexture(texture);
		else
			shape.setFillColor(ColorsMap[lifes]);
		if (bonus) init_object();
	}

	virtual ~Block() = default;

	bool is_deaf()
	{
		return lifes == 0;
	}

	bool is_const()
	{
		return lifes == 12;
	}

	size_t get_bonus()
	{
		return bonus;
	}

	virtual void init_object() override { v.y = 5; }
	virtual float get_velocity() override { return sqrt(v.x * v.x + v.y * v.y); }
	virtual void set_velocity(float dr) override {}
	virtual sf::Shape& get_shape() override { return shape; }
	virtual void update(bool contact = false) 
	{
		if (bonus > 0) shape.move(v);
		if (contact && (lifes != 12))
		{
			lifes--;
			if (lifes > 0) shape.setFillColor(ColorsMap[lifes]);
		}
	};
};

