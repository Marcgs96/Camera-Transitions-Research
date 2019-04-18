#pragma once
#include "Transition.h"
class Zoom :
	public Transition
{

private:
	float current_scale = 1;
	float target_scale;
	float normal_scale = 1;

	int final_width, final_height, start_width, start_height, current_width, current_height;

public:
	Zoom(float transition_time, float target_scale);
	~Zoom();

	void Entering();
	void Exiting();

	void SetTargetScale(int target_scale);
};

