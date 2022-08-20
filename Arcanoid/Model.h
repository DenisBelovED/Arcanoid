#pragma once
#include <SFML/Graphics.hpp>
#include "GameObject.h"
#include "Ball.h"
#include "Platform.h"
#include "Block.h"
#include "MapObjects.h"

class Model
{
private:
	MapObjects* game_map;
	std::vector<GameObject*> rendering_objects;
	size_t scr_w, scr_h;

	void generate_game(size_t blocks_count)
	{
		game_map = new MapObjects(scr_w, scr_h, blocks_count);
	}
public:
	void set_control_key(int key_code)
	{
		switch (key_code)
		{
		case sf::Keyboard::Key::Unknown:
			game_map->platform->stop();
			break;
		case sf::Keyboard::Left:
			game_map->platform->move_left();
			break;
		case sf::Keyboard::Right:
			game_map->platform->move_right();
			break;
		}
	}
	int update_world()
	{
		sf::FloatRect
			block_bnd,
			ball_bnd,
			plt_bnd = game_map->platform->get_shape().getGlobalBounds();
		
		std::vector<Ball*>::iterator fix_ball_it = game_map->balls.begin();
		for (int ball_it = 0; ball_it < game_map->balls.size(); ball_it++)
		{
			ball_bnd = game_map->balls[ball_it]->get_shape().getGlobalBounds();
			if (ball_bnd.intersects(plt_bnd))
			{
				game_map->balls[ball_it]->inverse_y();
				// TODO
			}
			std::vector<Block*>::iterator fix_block_it = game_map->blocks.begin();
			for (int block_it = 0; block_it < game_map->blocks.size(); block_it++)
			{
				block_bnd = game_map->blocks[block_it]->get_shape().getGlobalBounds();
				if (ball_bnd.intersects(block_bnd))
				{
					game_map->blocks[block_it]->update(true);
					if (game_map->blocks[block_it]->is_deaf())
					{
						delete game_map->blocks[block_it];
						game_map->blocks.erase(fix_block_it + block_it);
					}
					game_map->balls[ball_it]->inverse_y(); // TODO full cases
				}
			}
			if (ball_bnd.top >= scr_h)
			{
				game_map->balls.erase(fix_ball_it + ball_it);
				if (game_map->balls.empty())
					return 1; // MISSION FAIL CODE
				delete game_map->balls[ball_it];
			}
			game_map->balls[ball_it]->update();
		}
		game_map->platform->update();

		if (game_map->blocks.empty())
			return 2; // VICTORY CODE
		return 0; // GAME CONTINUE CODE
	}
	std::vector<GameObject*>& get_objects_shape()
	{
		rendering_objects.clear();
		rendering_objects.push_back(game_map->platform);
		for (Ball* b : game_map->balls)
			rendering_objects.push_back(b);
		for (Block* b : game_map->blocks)
			rendering_objects.push_back(b);
		return rendering_objects;
	}
	std::vector<GameObject*>& get_vin_shape()
	{
		rendering_objects.clear();
		rendering_objects.push_back(game_map->game_vin_block);
		return rendering_objects;
	}
	std::vector<GameObject*>& get_fail_shape()
	{
		rendering_objects.clear();
		rendering_objects.push_back(game_map->game_over_block);
		return rendering_objects;
	}
	Model(size_t scr_w, size_t scr_h, size_t blocks_count)
	{
		Model::scr_h = scr_h;
		Model::scr_w = scr_w;
		generate_game(blocks_count);
	}
};