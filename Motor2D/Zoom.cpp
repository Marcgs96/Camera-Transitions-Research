#include "Zoom.h"
#include "j1App.h"
#include "Render.h"
#include "Window.h"
#include "p2Log.h"


Zoom::Zoom(float transition_time, float target_scale) : Transition(transition_time)
{
	this->target_scale = target_scale;
	start_width = App->render->camera.w;
	start_height = App->render->camera.h;
	final_width = App->render->camera.w / target_scale;
	final_height = App->render->camera.h / target_scale;
	current_width = App->render->camera.w;
	current_height = App->render->camera.h;
}

Zoom::~Zoom()
{
}

void Zoom::Entering()
{
	Transition::Entering();

	float percent = current_time->ReadSec()*(1 / transition_time);

	float normalized_scale = LerpValue(percent, normal_scale, target_scale);

	float next_width = LerpValue(percent, start_width, final_width);
	float next_height = LerpValue(percent, start_height, final_height);

	float step_x = next_width - current_width;
	float step_y = next_height - current_height;

	LOG("%f", step_x);
	App->render->camera.x += step_x;
	App->render->camera.y += step_y;

	current_scale = normalized_scale;
	SDL_RenderSetScale(App->render->renderer, normalized_scale, normalized_scale);
	current_height = next_height;
	current_width = next_width;
}

void Zoom::Exiting()
{
	Transition::Exiting();

	current_scale = normal_scale;
	SDL_RenderSetScale(App->render->renderer, normal_scale, normal_scale);
}

void Zoom::SetTargetScale(int target_scale)
{
	this->target_scale = target_scale;
}