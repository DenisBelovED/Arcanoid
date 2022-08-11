#pragma once
#include <SFML/Graphics.hpp>
#include "GameObject.h"
#include "Ball.h"
#include "Platform.h"
#include "Block.h"
#include <iostream>
#include <map>

class Model
{
private:
	sf::Texture game_over_texture, game_vin_texture;
	Block *game_over_block, *game_vin_block;
	RandomGenerator<int>* rand_life_ptr = new RandomGenerator<int>(1, 11);

	std::vector<GameObject*> objects;
	std::map<int, GameObject*> objects_map; // 0 - platform, 10-99 - ball id, 100-999 - block id
	size_t scr_w, scr_h, blocks_count, balls_count = 1;

	void generate_game()
	{
		float
			scr_cw(scr_w / 2), scr_ch(scr_h / 2),
			platform_w(scr_w / 4), platform_h(scr_h / 30), velocity(5),
			ball_size(10), block_h(20), block_w(40), panel_h(5), panel_w(70);
		auto game_over_texture_size = game_over_texture.getSize();
		auto game_vin_texture_size = game_vin_texture.getSize();
		
		game_over_block = new Block(
			scr_cw - game_over_texture_size.x / 2,
			scr_ch - game_over_texture_size.y / 2,
			(size_t)10,
			game_over_texture_size.x,
			game_over_texture_size.y,
			&game_over_texture
		);

		game_vin_block = new Block(
			scr_cw - game_vin_texture_size.x / 2,
			scr_ch - game_vin_texture_size.y / 2,
			(size_t)10,
			game_vin_texture_size.x,
			game_vin_texture_size.y,
			&game_vin_texture
		);

		Ball* ball = new Ball(
			scr_cw, 
			scr_ch, 
			(float)scr_w,
			(float)scr_h, 
			ball_size
		);
		objects_map[ball_id] = ball;
		objects.push_back(ball);

		Platform* platform = new Platform(
			(size_t)platform_w,
			(size_t)platform_h,
			(scr_w - platform_w) / 2,
			scr_h - ball_size * 2,
			(float)scr_w, 
			(float)scr_h,
			velocity
		);
		objects_map[platform_id] = platform;
		objects.push_back(platform);

		for (int i = 1; i <= blocks_count; i++)
		{
			Block* b_tmp = new Block(
				scr_cw / 4 + 100 * i,
				scr_ch / 4 + 100 * i,
				(size_t)(rand_life_ptr->get_int()),
				50,
				30
			);
			objects_map[block_id + i - 1] = b_tmp;
			objects.push_back(b_tmp);
		}
	}
public:
	enum obj_id
	{
		platform_id = 0,
		ball_id = 10,
		block_id = 100
	};
	void set_control_key(int key_code)
	{
		switch (key_code)
		{
		case sf::Keyboard::Key::Unknown:
			((Platform*)objects_map[platform_id])->stop();
			break;
		case sf::Keyboard::Left:
			((Platform*)objects_map[platform_id])->move_left();
			break;
		case sf::Keyboard::Right:
			((Platform*)objects_map[platform_id])->move_right();
			break;
		}
	}
	int update_world()
	{
		Platform* plt = ((Platform*)objects_map[platform_id]);
		Ball* ball = ((Ball*)objects_map[ball_id]);

		sf::FloatRect
			ball_bnd = ball->get_shape().getGlobalBounds(),
			plt_bnd = plt->get_shape().getGlobalBounds();

		if (ball_bnd.intersects(plt_bnd))
			ball->inverse_y();

		for (int i = 0; i < blocks_count; i++)
		{
			sf::FloatRect block_bnd = objects_map[block_id + i]->get_shape().getGlobalBounds();
			if (ball_bnd.intersects(block_bnd))
			{
				objects_map[block_id + i]->update(true);
				if (objects_map[block_id + i] == nullptr)
				{
					objects_map.erase(block_id + i);
					blocks_count--;
				}
				ball->inverse_y(); // TODO full cases
			}
		}
		for (auto e = objects.begin(); e != objects.end(); ++e)
			if (*e == nullptr)
			{
				objects.erase(e);
				break;
			}
		if (blocks_count == 0)
		{
			objects.push_back(game_vin_block);
			return 2; // VICTORY CODE
		}

		if (ball_bnd.top >= scr_h)
		{
			balls_count--;
			if (balls_count == 0)
			{
				objects.push_back(game_over_block);
				return 1; // MISSION FAIL CODE
			}
			objects_map.erase(ball_id);
			for (auto e = objects.begin(); e != objects.end(); ++e)
				if (*e == ball)
				{
					objects.erase(e);
					break;
				}
			delete ball;
		}
		for (GameObject* g : objects)
			g->update();
		return 0; // GAME CONTINUE CODE
	}
	std::vector<GameObject*>& get_objects_shape()
	{
		return objects;
	}
	Model(size_t scr_w, size_t scr_h, size_t blocks_count)
	{
		if (!game_over_texture.loadFromFile("C:/Users/Denis/Documents/Политех/C++/Arcanoid/Arcanoid/data/game_over.png"))
			std::cout << "TEXTURE data/game_over.png NOT FOUND";
		if (!game_vin_texture.loadFromFile("C:/Users/Denis/Documents/Политех/C++/Arcanoid/Arcanoid/data/game_vin.png"))
			std::cout << "TEXTURE data/game_vin.png NOT FOUND";
		Model::scr_h = scr_h;
		Model::scr_w = scr_w;
		Model::blocks_count = blocks_count;
		generate_game();
	}
};

