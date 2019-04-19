#pragma once
#include "Transition.h"
#include "p2Point.h"
#include <vector>

class Bars :
	public Transition
{
private:
	Color color = Black;
	bool is_scene_change = false;
	int scene_to_change = 0;

	uint width, height, square_width, square_height;
	std::vector<iPoint>positions;

public:
	Bars(float transition_time, bool is_scene_change = false, int scene_to_change = 0, bool horizontal = false, Color color = Black);
	~Bars();

	void Entering();
	void Action();
	void Exiting();

	void SetColor(Color color);
	void DrawBars(int num_Bars);
};

