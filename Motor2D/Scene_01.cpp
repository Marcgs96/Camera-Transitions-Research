#include "p2Defs.h"
#include "p2Log.h"
#include "j1App.h"
#include "Input.h"
#include "Textures.h"
#include "Audio.h"
#include "Render.h"
#include "Window.h"
#include "Map.h"
#include "TransitionManager.h"
#include "SceneManager.h"
#include "Scene_01.h"



Scene_01::Scene_01()
{
}


Scene_01::~Scene_01()
{
}

bool Scene_01::Start()
{
	App->map->Load("scene_01.tmx");
	App->render->camera.x = start_camera_x;

	return true;
}

bool Scene_01::PreUpdate()
{
	int mouse_x, mouse_y;
	App->input->GetMousePosition(mouse_x, mouse_y);

	iPoint world_mouse_position = App->render->ScreenToWorld(mouse_x, mouse_y);

	if (!App->transition_manager->transitioning)
	{

		if (App->input->GetKey(SDL_SCANCODE_1) == KEY_DOWN)
			App->transition_manager->CreateFadeTransition(1.0F, true, SCENE_02, Black);

		if (App->input->GetKey(SDL_SCANCODE_2) == KEY_DOWN)
			App->transition_manager->CreateCameraTranslation(1.0F, world_mouse_position);

		//TODO 06
		//Uncomment this code and introduce a case for your wipe transition!
		//Try all transitions and choose one possible for your game or try design another one.

		if (App->input->GetKey(SDL_SCANCODE_4) == KEY_DOWN)
			App->transition_manager->CreateBarsTransition(3.0F, true, SCENE_02, true, Black);

		if (App->input->GetKey(SDL_SCANCODE_5) == KEY_DOWN)
			App->transition_manager->CreateSquaresTransition(3.0F, true, SCENE_02, Black);

		if (App->input->GetKey(SDL_SCANCODE_6) == KEY_DOWN)
			App->transition_manager->CreateZoomTransition(3.0F, 2.0F);

		if (App->input->GetKey(SDL_SCANCODE_7) == KEY_DOWN)
			App->transition_manager->CreateDissolveTransition(3.0F, SCENE_02);
	}

	return true;
}

bool Scene_01::Update(float dt)
{
	App->map->Draw();
	return true;
}

bool Scene_01::PostUpdate()
{
	return false;
}

bool Scene_01::CleanUp()
{
	return false;
}
