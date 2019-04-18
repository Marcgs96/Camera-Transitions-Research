#pragma once
#include "Scene.h"
class Scene_02 :
	public Scene
{
public:
	Scene_02();
	~Scene_02();

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

