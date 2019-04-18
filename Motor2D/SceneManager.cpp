#include "TestingScene.h"
#include "SceneManager.h"



SceneManager::SceneManager()
{
	name = "scene_manager";
}


SceneManager::~SceneManager()
{

}

bool SceneManager::Awake(pugi::xml_node &)
{
	current_scene = new TestingScene();
	return true;
}

bool SceneManager::Start()
{
	current_scene->Start();
	return true;
}

bool SceneManager::PreUpdate()
{
	current_scene->PreUpdate();
	return true;
}

bool SceneManager::Update(float dt)
{
	current_scene->Update(dt);
	return true;
}

bool SceneManager::PostUpdate()
{
	current_scene->PostUpdate();
	return true;
}

bool SceneManager::CleanUp()
{
	current_scene->CleanUp();
	return true;
}

bool SceneManager::Load(pugi::xml_node &xml)
{
	current_scene->Load(xml);
	return true;
}

bool SceneManager::Save(pugi::xml_node &xml) const
{
	current_scene->Save(xml);
	return true;
}

//Scene unloads current scene, then creates and loads new scene.
void SceneManager::ChangeScene(int new_scene)
{
	current_scene->CleanUp();

	switch (new_scene)
	{
	case MENU:
		break;
	case MAP:
		break;
	case COMBAT:
		break;
	case TESTING:
		current_scene = new TestingScene();
		break;
	}

	current_scene->Start();
}
