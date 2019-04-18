#pragma once
#include "Transition.h"

class CameraTranslation :
	public Transition
{
private:
	iPoint origin;
	iPoint destination;

	float distance;
	iPoint direction;
public:
	CameraTranslation(float transition_time, iPoint destination);
	~CameraTranslation();

	void Entering();

	void SetOriginAndDestination(iPoint origin, iPoint destination);

};

