#pragma once
#include <SFML/Graphics.hpp>
#include "GameObject.h"
#include "Ball.h"
#include "Platform.h"
#include<iostream>

class Model
{
private:
	std::vector<GameObject*> objects;
	Platform* platform;
	size_t scr_w, scr_h;

	void generate_game()
	{
		float
			scr_cw(scr_w / 2), scr_ch(scr_h / 2),
			platform_w(scr_w / 4), platform_h(scr_h / 30), velocity(5),
			ball_size(10), block_h(20), block_w(40), panel_h(5), panel_w(70);

		Ball* ball = new Ball(scr_cw, scr_ch, (float)scr_w, (float)scr_h, ball_size);
		platform = new Platform((size_t)platform_w, (size_t)platform_h, (scr_w - platform_w) / 2, scr_h - ball_size * 2, (float)scr_w, (float)scr_h, velocity);

		objects.push_back(ball);
		objects.push_back(platform);
	}
public:
	void set_control_key(int key_code)
	{
		switch (key_code)
		{
		case sf::Keyboard::Key::Unknown:
			platform->stop();
			break;
		case sf::Keyboard::Left:
			platform->move_left();
			break;
		case sf::Keyboard::Right:
			platform->move_right();
			break;
		}
	}
	void update_world()
	{
		for (GameObject* g : objects)
		{
			g->update();
		}
	}
	std::vector<GameObject*>& get_objects_shape()
	{
		return objects;
	}
	Model(size_t scr_w, size_t scr_h)
	{
		Model::scr_h = scr_h;
		Model::scr_w = scr_w;
		generate_game();
	}
};

