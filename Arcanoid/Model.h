#pragma once
#include <SFML/Graphics.hpp>
#include "GameObject.h"
#include "Ball.h"
#include<iostream>

class Model
{
private:
	std::vector<GameObject*> objects;
	size_t scr_w, scr_h;

	void generate_game()
	{
		float scr_cw = scr_w / 2, scr_ch = scr_h / 2;
		float ball_size(10), block_h(20), block_w(40), panel_h(5), panel_w(70);
		auto x = new Ball(scr_cw, scr_ch, ball_size);
		GameObject* y = x;
		objects.push_back(y);
	}
public:
	void set_control_key(int key_code)
	{
		//RandomGenerator<int> selector(0, 10);
		//std::cout << selector.get_int() << std::endl;
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

