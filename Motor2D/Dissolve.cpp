#include "Dissolve.h"
#include "SceneManager.h"
#include "j1App.h"
#include "Render.h"
#include "Window.h"
#include "p2Log.h"
#include "Render.h"

Dissolve::Dissolve(float transition_time, int scene_to_change) : Transition(transition_time)
{
	this->scene_to_change = scene_to_change;
	this->color = color;

	uint width, height;
	App->win->GetWindowSize(width, height);

	rect = { 0, 0, (int)width, (int)height };
	SDL_SetRenderDrawBlendMode(App->render->renderer, SDL_BLENDMODE_BLEND);

	text = SDL_CreateTexture(App->render->renderer, SDL_PIXELFORMAT_RGBA8888, SDL_TEXTUREACCESS_TARGET, width, height);
}

Dissolve::~Dissolve()
{
}

void Dissolve::Entering()
{
	Transition::Entering();
}

void Dissolve::Action()
{
	SDL_SetRenderTarget(App->render->renderer, text);
	SDL_SetTextureBlendMode(text, SDL_BLENDMODE_BLEND);

	App->scene_manager->ChangeScene(scene_to_change);

	Transition::Action();
}

void Dissolve::Exiting()
{
	Transition::Exiting();

	float alpha = LerpValue(percent, 255, 0);

	SDL_SetTextureAlphaMod(text, alpha);

	if (current_time->ReadSec() >= transition_time)
	{
		SDL_SetRenderTarget(App->render->renderer, NULL);
	}
}
