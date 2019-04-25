#pragma once
#include "Transition.h"


class SDL_Texture;
class SDL_Surface;

class Dissolve :
	public Transition
{
private:
	Color color = Black;
	bool is_scene_change = false;
	int scene_to_change = 0;

	uint width, height;

	SDL_Texture* target_text = nullptr;
	SDL_Texture* capture_text = nullptr;
	SDL_Surface* capture_surf = nullptr;
	SDL_Rect rect;

public:
	Dissolve(float transition_time, int scene_to_change = 0);
	~Dissolve();

	void Entering();
	void Action();
	void Exiting();

};
