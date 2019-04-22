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

	float step_x = LerpValue(percent, origin.x, destination.x);
	float step_y = LerpValue(percent, origin.y, destination.y);


	App->render->camera.x = step_x;
	App->render->camera.y = step_y;
}

void CameraTranslation::SetOriginAndDestination(iPoint origin, iPoint destination)
{
	this->origin = origin;
	this->destination = destination;
}
