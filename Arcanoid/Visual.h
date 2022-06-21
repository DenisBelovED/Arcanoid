#pragma once
#include <SFML/Window.hpp>
#include <SFML/Graphics.hpp>
#include "GameObject.h"

class Visual
{
private:
	sf::RenderWindow* window;
public:
	Visual(size_t width, size_t height)
	{
		window = new sf::RenderWindow({ (unsigned int)width, (unsigned int)height }, "Arkanoid");
		window->setFramerateLimit(60);
	}
	~Visual()
	{
		delete window;
	}
	void clear()
	{
		window->clear(sf::Color::Black);
	}
	void show()
	{
		window->display();
	}
	void draw_objects(std::vector<GameObject*>& shapes)
	{
		for (GameObject* g : shapes)
		{
			sf::Shape& z = g->get_shape();
			window->draw(z);
		}
	}
};