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
	size_t scr_w, scr_h, const_block_count;
	float near_radius, x_centroid, y_centroid, br_x_centroid, br_y_centroid,
		vx, vy, alpha;
	RandomGenerator<float>* rand_bonus_ptr = new RandomGenerator<float>(0, 1);

	void generate_game(size_t blocks_count)
	{
		game_map = new MapObjects(scr_w, scr_h, blocks_count);
		for (Block* b : game_map->blocks)
			if (b->is_const())
				const_block_count++;
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
			br_ball_bnd,
			bonus_bnd,
			plt_bnd = game_map->platform->get_shape().getGlobalBounds();
		Ball *ball_obj, *br_ball_obj;
		
		std::vector<Ball*>::iterator fix_ball_it = game_map->balls.begin();
		std::vector<Block*>::iterator bonus_it = game_map->bonuses.begin();

		for (int ball_it = 0; ball_it < game_map->balls.size(); ball_it++)
		{
			ball_obj = game_map->balls[ball_it];
			near_radius = ball_obj->radius * sqrt(2) * 0.5;
			ball_bnd = ball_obj->get_shape().getGlobalBounds();
			x_centroid = ball_bnd.left + ball_bnd.width * 0.5;
			y_centroid = ball_bnd.top + ball_bnd.height * 0.5;
			if (ball_bnd.intersects(plt_bnd))
			{
				if (
					(plt_bnd.left - near_radius < x_centroid) &&
					(x_centroid < plt_bnd.left + plt_bnd.width + near_radius) &&
					(plt_bnd.top - near_radius > y_centroid) &&
					(ball_obj->scalar_mul(0, -1) <= 0)
					)
					ball_obj->inverse_y();
				else
					ball_obj->inverse_x();
			}

			for (int br_ball_it = 0; br_ball_it < game_map->balls.size(); br_ball_it++)
				if (ball_it != br_ball_it)
				{
					br_ball_obj = game_map->balls[br_ball_it];
					br_ball_bnd = br_ball_obj->get_shape().getGlobalBounds();
					br_x_centroid = br_ball_bnd.left + br_ball_bnd.width * 0.5;
					br_y_centroid = br_ball_bnd.top + br_ball_bnd.height * 0.5;
					//float distance = sqrt(pow(x_centroid - br_x_centroid, 2) + pow(y_centroid - br_y_centroid, 2));
					if (ball_bnd.intersects(br_ball_bnd)) // && (distance >= (ball_obj->radius * 2 + 1e-1)))
					{
						vx = br_x_centroid - x_centroid;
						vy = br_y_centroid - y_centroid;
						alpha = ball_obj->scalar_mul(vx, vy) / (ball_obj->get_velocity() * sqrt(vx * vx + vy * vy));
						ball_obj->rotate(alpha);
						vx = x_centroid - br_x_centroid;
						vy = y_centroid - br_y_centroid;
						alpha = br_ball_obj->scalar_mul(vx, vy) / (br_ball_obj->get_velocity() * sqrt(vx * vx + vy * vy));
						br_ball_obj->rotate(alpha);
					}
				}

			std::vector<Block*>::iterator fix_block_it = game_map->blocks.begin();
			for (int block_it = 0; block_it < game_map->blocks.size(); block_it++)
			{
				block_bnd = game_map->blocks[block_it]->get_shape().getGlobalBounds();
				if (ball_bnd.intersects(block_bnd))
				{
					game_map->blocks[block_it]->update(true);

					if (
						(x_centroid <= block_bnd.left - near_radius) || 
						(block_bnd.left + block_bnd.width + near_radius <= x_centroid)
						) ball_obj->inverse_x();

					if (
						(y_centroid <= block_bnd.top - near_radius) ||
						(block_bnd.top + block_bnd.height + near_radius <= y_centroid)
						) ball_obj->inverse_y();

					if (game_map->blocks[block_it]->is_deaf())
					{
						float p = rand_bonus_ptr->get_float();
						if ((0.4 <= p) && (p < 0.6))
							game_map->bonuses.push_back(
								new Block(block_bnd.left + block_bnd.width * 0.5, block_bnd.top + block_bnd.height * 0.5, 5, 10, 10, nullptr, 1)
							);
						if ((0.6 <= p) && (p < 0.8))
							game_map->bonuses.push_back(
								new Block(block_bnd.left + block_bnd.width * 0.5, block_bnd.top + block_bnd.height * 0.5, 3, 10, 10, nullptr, 2)
							);
						if ((0.8 <= p) && (p <= 1))
							game_map->bonuses.push_back(
								new Block(block_bnd.left + block_bnd.width * 0.5, block_bnd.top + block_bnd.height * 0.5, 1, 10, 10, nullptr, 3)
							);
						delete game_map->blocks[block_it];
						game_map->blocks.erase(fix_block_it + block_it);
					}
				}
			}

			ball_obj->update();
			
			if (ball_bnd.top >= scr_h)
			{
				game_map->balls.erase(fix_ball_it + ball_it);
				if (game_map->balls.empty())
					return 1; // MISSION FAIL CODE
				delete ball_obj;
			}
		}
		for (int bonus_id = 0; bonus_id < game_map->bonuses.size(); bonus_id++)
		{
			game_map->bonuses[bonus_id]->update();
			bonus_bnd = game_map->bonuses[bonus_id]->get_shape().getGlobalBounds();
			if (bonus_bnd.intersects(plt_bnd))
			{
				switch (game_map->bonuses[bonus_id]->get_bonus())
				{
				case 0:
					break;
				case 1:
					for (Ball* b: game_map->balls)
						b->set_velocity(rand_bonus_ptr->get_float() + 0.7);
					break;
				case 2:
					game_map->platform->get_shape().scale((rand_bonus_ptr->get_float() + 0.5), 1);
					break;
				case 3:
					game_map->balls.push_back(
						new Ball(plt_bnd.left + plt_bnd.width * 0.5, scr_h - game_map->balls[0]->radius * 6, (float)scr_w, (float)scr_h, game_map->balls[0]->radius * 2)
					);
					break;
				}
				delete game_map->bonuses[bonus_id];
				game_map->bonuses.erase(bonus_it + bonus_id);
			}
			if (bonus_bnd.top > scr_h)
			{
				delete game_map->bonuses[bonus_id];
				game_map->bonuses.erase(bonus_it + bonus_id);
			}
		}
		game_map->platform->update();

		if (game_map->blocks.size() - const_block_count == 0)
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
		for (Block* b : game_map->bonuses)
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
	~Model()
	{
		delete game_map, rand_bonus_ptr;
		//for (int i = 0; i < rendering_objects.size(); i++)
		//	delete rendering_objects[i];
		rendering_objects.clear();
	}
};