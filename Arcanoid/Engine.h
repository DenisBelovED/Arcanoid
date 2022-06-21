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
		while (control->runtime_status())
		{
			visual->clear();
			model->set_control_key(control->request_key());
			model->update_world();
			visual->draw_objects(model->get_objects_shape());
			visual->show();
		}
	}
};

