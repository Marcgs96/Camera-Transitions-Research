#include "CameraTranslation.h"
#include "j1App.h"
#include "Render.h"
#include "p2Log.h"
#include "Window.h"
#include <cmath>


CameraTranslation::CameraTranslation(float transition_time, iPoint destination) : Transition(transition_time)
{
	uint w, h;
	App->win->GetWindowSize(w, h);

	origin = { App->render->camera.x, App->render->camera.y };
	this->destination = {(int)(-destination.x + w * 0.5), (int)(-destination.y + h * 0.5)};
}

CameraTranslation::~CameraTranslation()
{

}

void CameraTranslation::Entering()
{
	Transition::Entering();

	float percent = current_time->ReadSec()*(1 / transition_time);

	float step_x = origin.x + percent * (destination.x - origin.x);
	float step_y = origin.y + percent * (destination.y - origin.y);


	App->render->camera.x = step_x;
	App->render->camera.y = step_y;
}

void CameraTranslation::SetOriginAndDestination(iPoint origin, iPoint destination)
{
	this->origin = origin;
	this->destination = destination;
}
