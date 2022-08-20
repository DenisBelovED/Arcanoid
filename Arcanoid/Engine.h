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
	size_t scr_w = 800, scr_h = 640, blocks_count = 3;

	Engine()
	{
		visual = new Visual(scr_w, scr_h);
		model = new Model(scr_w, scr_h, blocks_count);
		control = new Control();
	}
	~Engine()
	{
		delete visual;
		delete model;
		delete control;
	}
	void game_loop()
	{
		int game_code = 0;
		while (control->runtime_status())
		{
			visual->clear();
			model->set_control_key(control->request_key());
			game_code = model->update_world();
			switch (game_code)
			{
			default:
				visual->draw_objects(model->get_objects_shape());
				visual->show();
				break;
			case 1:
				visual->draw_objects(model->get_fail_shape());
				visual->show();
				while (sf::Keyboard::Key::Space != control->request_key()) continue;
				delete model;
				model = new Model(scr_w, scr_h, blocks_count);
				break;
			case 2:
				visual->draw_objects(model->get_vin_shape());
				visual->show();
				while (sf::Keyboard::Key::Space != control->request_key()) continue;
				delete model;
				model = new Model(scr_w, scr_h, blocks_count);
				break;
			}
		}
	}
};

