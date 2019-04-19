#include "Wipe.h"
#include "SceneManager.h"
#include "j1App.h"
#include "Render.h"
#include "Window.h"
#include "p2Log.h"


Wipe::Wipe(float transition_time, bool is_scene_change, int scene_to_change, Color color) : Transition(transition_time)
{
	this->is_scene_change = is_scene_change;
	this->scene_to_change = scene_to_change;
	this->color = color;



	App->win->GetWindowSize(width, height);
	rect = { -(int)width, 0, (int)width, (int)height };
	SDL_SetRenderDrawBlendMode(App->render->renderer, SDL_BLENDMODE_BLEND);
}

Wipe::~Wipe()
{
}

void Wipe::Entering()
{
	Transition::Entering();

	float percent = current_time->ReadSec()*(1 / transition_time);

	float normalized_x_position = LerpValue(percent, -(int)width, 0);

	if (normalized_x_position >= 0)
		rect.x = 0;
	else rect.x = normalized_x_position;

	DrawRect();
}

void Wipe::Action()
{
	Transition::Action();

	DrawRect();

	if (is_scene_change)
	{
		App->scene_manager->ChangeScene(scene_to_change);
	}
}

void Wipe::Exiting()
{
	Transition::Exiting();

	float percent = current_time->ReadSec()*(1 / transition_time);

	float normalized_x_position = LerpValue(percent, 0, -(int)width);

	if(normalized_x_position <= -(int)width)
		rect.x = -(int)width;
	else rect.x = normalized_x_position;

	DrawRect();
}

void Wipe::SetColor(Color color)
{
	this->color = color;
}

void Wipe::DrawRect()
{
	SDL_SetRenderDrawColor(App->render->renderer, color.r, color.g, color.b, 255);
	SDL_RenderFillRect(App->render->renderer, &rect);
}
