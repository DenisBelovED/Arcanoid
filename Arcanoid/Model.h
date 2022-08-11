#pragma once
#include <SFML/Graphics.hpp>
#include "GameObject.h"
#include "Ball.h"
#include "Platform.h"
#include <iostream>
#include <map>

class Model
{
private:
	std::vector<GameObject*> objects;
	std::map<int, GameObject*> objects_map; // 0 - platform, 10-99 - ball id, 100-999 - block id
	size_t 
		scr_w, scr_h,
		balls_count = 1, blocks_count = 20;

	sf::Font font;
	sf::Text game_over_text;

	void generate_game()
	{
		float
			scr_cw(scr_w / 2), scr_ch(scr_h / 2),
			platform_w(scr_w / 4), platform_h(scr_h / 30), velocity(5),
			ball_size(10), block_h(20), block_w(40), panel_h(5), panel_w(70);

		Ball* ball = new Ball(
			scr_cw, 
			scr_ch, 
			(float)scr_w,
			(float)scr_h, 
			ball_size
		);
		objects_map[ball_id] = ball;

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


		objects.push_back(ball);
		objects.push_back(platform);
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
		if (ball_bnd.top >= scr_h)
		{
			balls_count--;
			if (balls_count == 0) return 1; // GAME OVER CODE
			objects_map.erase(ball_id);
			for (auto e = objects.begin(); e != objects.end(); ++e)
				if (*e == ball)
				{
					objects.erase(e);
					break;
				}
			delete ball;
			//game_over_text..draw(game_over_text);
		}
		for (GameObject* g : objects)
			g->update();
		return 0; // GAME CONTINUE CODE
	}
	std::vector<GameObject*>& get_objects_shape()
	{
		return objects;
	}
	Model(size_t scr_w, size_t scr_h)
	{
		if (font.loadFromFile("arial.ttf")) 
		{
			game_over_text.setFont(font);
			game_over_text.setString("GAME OVER!");
			game_over_text.setCharacterSize(30);
			game_over_text.setOrigin(scr_w / 2, scr_h / 2);
			game_over_text.setFillColor(sf::Color::Red);
			game_over_text.setStyle(sf::Text::Bold);
		}
		else
			std::cout << "FONT NOT FOUND\n";
		Model::scr_h = scr_h;
		Model::scr_w = scr_w;
		generate_game();
	}
};

