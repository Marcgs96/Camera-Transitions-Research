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
	
	//TODO 02
	//Save your current interpolation value in a local variable. Use the LerpValue() function
	//We want the rect to cover the whole screen, make sure this new value is not bigger than 0
	//Assign it to the rect x attribute.
	//Remember to draw the rect
}

void Wipe::Action()
{
	Transition::Action();

	//TODO 03
	//Its time to make the scene change, remember to check if this is a scene change transition or not, 
	//draw the rect!
}

void Wipe::Exiting()
{
	Transition::Exiting();

	//TODO 04
	//Pretty similar to the Entering one but reversed!
}

void Wipe::SetColor(Color color)
{
	this->color = color;
}

void Wipe::DrawRect()
{
	//TODO 01
	//Fill the method DrawRect() by setting the render draw color and telling the render to fill your rect.
	//Remember to use your variables color and rect.
}
