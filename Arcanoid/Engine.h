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
		size_t scr_w(800), scr_h(640), blocks_count(3);
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
			switch (game_code)
			{
			default:
				game_code = model->update_world();
				break;
			case 1:
				break;
			case 2:
				break;
			}
			visual->draw_objects(model->get_objects_shape());
			visual->show();
		}
	}
};

