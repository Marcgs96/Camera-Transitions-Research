#pragma once
#include "Transition.h"
class Wipe :
	public Transition
{
private:
	Color color = Black;
	bool is_scene_change = false;
	int scene_to_change = 0;

	SDL_Rect rect;
	uint width, height;

public:
	Wipe(float transition_time, bool is_scene_change = false, int scene_to_change = 0, Color color = Black);
	~Wipe();

	void Entering();
	void Action();
	void Exiting();

	void SetColor(Color color);
	void DrawRect();
};

