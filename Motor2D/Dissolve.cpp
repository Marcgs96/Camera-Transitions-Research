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

	target_text = SDL_CreateTexture(App->render->renderer, SDL_PIXELFORMAT_RGBA8888, SDL_TEXTUREACCESS_TARGET, width, height);
	SDL_SetTextureBlendMode(target_text, SDL_BLENDMODE_BLEND);

}

Dissolve::~Dissolve()
{
}

void Dissolve::Entering()
{
	state = TransitionState::ACTION;
}

void Dissolve::Action()
{
	Transition::Action();

	App->scene_manager->ChangeScene(scene_to_change);
}

void Dissolve::Exiting()
{
	Transition::Exiting();

	float alpha = LerpValue(percent, 255, 0);
	int amod = SDL_SetTextureAlphaMod(target_text, alpha);
	LOG("amod %i alpha %f", amod, alpha);

	SDL_SetRenderTarget(App->render->renderer, target_text);

	//Clear screen
	SDL_SetRenderDrawColor(App->render->renderer, 0xFF, 0xFF, 0xFF, 0xFF);
	SDL_RenderClear(App->render->renderer);

	//Reset render target
	SDL_SetRenderTarget(App->render->renderer, NULL);

	//Show rendered to texture
	SDL_RenderCopy(App->render->renderer, target_text, NULL, NULL);

	//Update screen
	SDL_RenderPresent(App->render->renderer);
}
