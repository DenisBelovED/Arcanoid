#pragma once
#include <SFML/Window.hpp>
#include <SFML/Graphics.hpp>
#include <map>
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
	void draw_objects(std::map<int, GameObject*>& objects_map)
	{
		for (std::map<int, GameObject*>::iterator it = objects_map.begin(); it != objects_map.end(); ++it)
			window->draw(it->second->get_shape());
	}
};