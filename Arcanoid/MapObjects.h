#pragma once

class MapObjects
{
public:
	std::vector<Ball*> balls;
	std::vector<Block*> blocks;
	Block *game_over_block, *game_vin_block;
	Platform *platform;

	MapObjects(size_t win_w, size_t win_h, size_t block_count)
	{
		sf::Texture game_over_texture, game_vin_texture;
		RandomGenerator<int>* rand_life_ptr = new RandomGenerator<int>(1, 2);
		float
			scr_cw(win_w / 2), scr_ch(win_h / 2),
			platform_w(win_w / 4), platform_h(win_h / 30), velocity(5),
			ball_size(10), block_h(20), block_w(40), panel_h(5), panel_w(70);
		auto game_over_texture_size = game_over_texture.getSize();
		auto game_vin_texture_size = game_vin_texture.getSize();

		if (!game_over_texture.loadFromFile("C:/Users/Denis/Documents/Политех/C++/Arcanoid/Arcanoid/data/game_over.png")) // TODO
			std::cout << "TEXTURE data/game_over.png NOT FOUND";
		if (!game_vin_texture.loadFromFile("C:/Users/Denis/Documents/Политех/C++/Arcanoid/Arcanoid/data/game_vin.png")) // TODO
			std::cout << "TEXTURE data/game_vin.png NOT FOUND";

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
		
		platform = new Platform(
			(size_t)platform_w,
			(size_t)platform_h,
			(win_w - platform_w) / 2,
			win_h - ball_size * 2,
			(float)win_w,
			(float)win_h,
			velocity
		);

		Ball* b = new Ball(scr_cw, scr_ch, (float)win_w, (float)win_h, ball_size);
		balls.push_back(b);

		for (int i = 0; i < block_count; i++)
		{
			Block* b = new Block(scr_cw / 4 + 100 * i, scr_ch / 4 + 100 * i, (size_t)(rand_life_ptr->get_int()), 50, 30);
			blocks.push_back(b);
		}
	}
	~MapObjects()
	{
		for (int i = 0; i < balls.size(); i++)
			delete balls[i];
		for (int i = 0; i < blocks.size(); i++)
			delete blocks[i];
		delete game_over_block, game_vin_block, platform;
	}
};

