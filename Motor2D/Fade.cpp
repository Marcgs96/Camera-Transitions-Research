#include "Fade.h"
#include "SceneManager.h"
#include "j1App.h"
#include "Render.h"
#include "Window.h"
#include "p2Log.h"

Fade::Fade(float transition_time, bool is_scene_change, int scene_to_change, Color color) : Transition(transition_time)
{
	this->is_scene_change = is_scene_change;
	this->scene_to_change = scene_to_change;
	this->color = color;

	uint width, height;

	App->win->GetWindowSize(width, height);
	screen = { 0, 0, (int)width, (int)height };
	SDL_SetRenderDrawBlendMode(App->render->renderer, SDL_BLENDMODE_BLEND);
}

Fade::~Fade()
{
}

void Fade::Entering()
{
	Transition::Entering();

	float percent = current_time->ReadSec()*(1 / transition_time);

	float normalized_alpha = floor(LerpValue(percent, 0, 255));
	DrawFadeRect(normalized_alpha);
}

void Fade::Action()
{
	Transition::Action();

	DrawFadeRect(255.0F);

	if (is_scene_change)
	{
		App->scene_manager->ChangeScene(scene_to_change);
	}
}

void Fade::Exiting()
{
	Transition::Exiting();

	float percent = current_time->ReadSec()*(1 / transition_time);

	float normalized_alpha = floor(LerpValue(percent, 255, 0));

	DrawFadeRect(normalized_alpha);
}

void Fade::DrawFadeRect(float alpha_value)
{
	if (alpha_value > 255)alpha_value = 255;
	if (alpha_value < 0)alpha_value = 0;

	SDL_SetRenderDrawColor(App->render->renderer, color.r, color.g, color.b, alpha_value);
	SDL_RenderFillRect(App->render->renderer, &screen);
}

void Fade::SetColor(Color color)
{
	this->color = color;
}
