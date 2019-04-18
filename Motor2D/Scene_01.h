#pragma once
#include "Scene.h"
class Scene_01 :
	public Scene
{
public:

	Scene_01();
	~Scene_01();

	// Called before the first frame
	virtual bool Start();

	// Called before all Updates
	virtual bool PreUpdate();

	// Called each loop iteration
	virtual bool Update(float dt);

	// Called before all Updates
	virtual bool PostUpdate();

	// Called before quitting
	virtual bool CleanUp();

private:
	int start_camera_x = 425;
};

