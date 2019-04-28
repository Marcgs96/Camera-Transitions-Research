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
#include "Scene_02.h"



Scene_02::Scene_02()
{
}


Scene_02::~Scene_02()
{
}

bool Scene_02::Start()
{
	App->map->Load("scene_02.tmx");
	App->render->camera.x = start_camera_x;
	return true;
}

bool Scene_02::PreUpdate()
{
	int mouse_x, mouse_y;
	App->input->GetMousePosition(mouse_x, mouse_y);

	iPoint world_mouse_position = App->render->ScreenToWorld(mouse_x, mouse_y);

	if (!App->transition_manager->transitioning)
	{
		if (App->input->GetKey(SDL_SCANCODE_1) == KEY_DOWN)
			App->transition_manager->CreateFadeTransition(1.0F, true, SCENE_01, Black);

		if (App->input->GetKey(SDL_SCANCODE_2) == KEY_DOWN)
			App->transition_manager->CreateCameraTranslation(2.0F, world_mouse_position);

		if (App->input->GetKey(SDL_SCANCODE_3) == KEY_DOWN)
			App->transition_manager->CreateWipeTransition(1.0F, true, SCENE_01, Black);

		if (App->input->GetKey(SDL_SCANCODE_4) == KEY_DOWN)
			App->transition_manager->CreateBarsTransition(3.0F, true, SCENE_01, false, Black);

		if (App->input->GetKey(SDL_SCANCODE_5) == KEY_DOWN)
			App->transition_manager->CreateSquaresTransition(3.0F, true, SCENE_01, Black);

		if (App->input->GetKey(SDL_SCANCODE_6) == KEY_DOWN)
			App->transition_manager->CreateZoomTransition(3.0F, 2.0F);

		if (App->input->GetKey(SDL_SCANCODE_7) == KEY_DOWN)
			App->transition_manager->CreateDissolveTransition(3.0F, SCENE_01);
	}

	return true;
}

bool Scene_02::Update(float dt)
{
	App->map->Draw();
	return true;
}

bool Scene_02::PostUpdate()
{
	return false;
}

bool Scene_02::CleanUp()
{
	return false;
}
