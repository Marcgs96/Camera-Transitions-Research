#pragma once
#include "Transition.h"
class Fade :
	public Transition
{
private:
	Color color = Black;
	bool is_scene_change = false;
	int scene_to_change = 0;

	SDL_Rect screen;
public:
	Fade(float transition_time, bool is_scene_change = false, int scene_to_change = 0, Color color = Black);
	~Fade();

	void Entering();
	void Action();
	void Exiting();

	void DrawFadeRect(float alpha_value);
	void SetColor(Color color);
};

