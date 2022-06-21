#pragma once
#include "Model.h"
#include "Control.h"
#include "Visual.h"

class Engine
{
private:
	Visual* visual;
	Model* model;
	Control* control;
public:
	Engine()
	{
		size_t scr_w(800), scr_h(640);
		visual = new Visual(scr_w, scr_h);
		model = new Model(scr_w, scr_h);
	}
	~Engine()
	{
		delete visual;
		delete model;
		delete control;
	}
	void game_loop()
	{
		while (true)
		{
			visual->clear();
			if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Escape))
				break;
			visual->draw_objects(model->get_objects_shape());
			visual->show();
		}
	}
};

