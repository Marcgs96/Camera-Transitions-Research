#pragma once
#include "Transition.h"


class SDL_Texture;

class Dissolve :
	public Transition
{
private:
	Color color = Black;
	bool is_scene_change = false;
	int scene_to_change = 0;

	uint width, height;

	SDL_Texture* text = nullptr;
	SDL_Rect rect;

public:
	Dissolve(float transition_time, int scene_to_change = 0);
	~Dissolve();

	void Entering();
	void Action();
	void Exiting();

};
