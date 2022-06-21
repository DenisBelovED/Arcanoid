#pragma once
#include<SFML/Window.hpp>

class Control
{
private:
	bool runtime = true;
public:
	int request_key()
	{
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Escape)) runtime = false;
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Left)) return sf::Keyboard::Key::Left;
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Right)) return sf::Keyboard::Key::Right;
		return sf::Keyboard::Key::Unknown;
	}
	bool runtime_status() { return runtime; }
};

