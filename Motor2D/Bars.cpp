#include "Bars.h"
#include "SceneManager.h"
#include "j1App.h"
#include "Render.h"
#include "Window.h"
#include "p2Log.h"




Bars::Bars(float transition_time, bool is_scene_change, int scene_to_change, bool horizontal, Color color) : Transition(transition_time)
{
	this->is_scene_change = is_scene_change;
	this->scene_to_change = scene_to_change;
	this->color = color;

	App->win->GetWindowSize(width, height);
	SDL_SetRenderDrawBlendMode(App->render->renderer, SDL_BLENDMODE_BLEND);

	if (horizontal) {

		square_width = (int)((width / 9)+1);
		square_height = (int)(height / 16);

		for (int y = 0; y < 16; y++)
		{
			for (int x = 0; x < 9; x++)
			{
				positions.push_back({ (int)(x*square_width), (int)(y*square_height) });

			}
		}
	}
	else {
		square_width = (int)width / 16;
		square_height = (int)((height / 9)+1);

		for (int x = 0; x < 16; x++)
		{
			for (int y = 0; y < 9; y++)
			{
				positions.push_back({ (int)(x*square_width), (int)(y*square_height) });
			}
		}
	}
}

Bars::~Bars()
{
}

void Bars::Entering()
{
	Transition::Entering();

	int num_Bars = (int)LerpValue(percent, 0, 16*9);

	DrawBars(num_Bars);
}

void Bars::Action()
{
	DrawBars(16*9);

	if (is_scene_change)
	{
		App->scene_manager->ChangeScene(scene_to_change);
	}

	Transition::Action();
}

void Bars::Exiting()
{
	Transition::Exiting();

	int num_Bars = (int)LerpValue(percent, 16*9, 0);

	DrawBars(num_Bars);
}

void Bars::SetColor(Color color)
{
}

void Bars::DrawBars(int num_Bars)
{
	SDL_Rect* Bars = new SDL_Rect[num_Bars];

	for (int i = 0; i < num_Bars; i++)
	{
		Bars[i].x = positions[i].x;
		Bars[i].y = positions[i].y;
		Bars[i].w = square_width;
		Bars[i].h = square_height;
	}

	SDL_SetRenderDrawColor(App->render->renderer, color.r, color.g, color.b, 255);
	SDL_RenderFillRects(App->render->renderer, Bars, num_Bars);
}

