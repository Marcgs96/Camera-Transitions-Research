#ifndef _SCENE_MANAGER_H_
#define _SCENE_MANAGER_H_

#include "Module.h"
#include "Scene.h"

enum SceneType{
	MENU,
	MAP,
	COMBAT,
	TESTING
};

class SceneManager :
	public Module
{
public:
	SceneManager();
	~SceneManager();

	// Called before render is available
	virtual bool Awake(pugi::xml_node&);
	// Called before the first frame
	virtual bool Start();
	// Called each loop iteration
	virtual bool PreUpdate();
	// Called each loop iteration
	virtual bool Update(float dt);
	// Called each loop iteration
	virtual bool PostUpdate();
	// Called before quitting
	virtual bool CleanUp();
	virtual bool Load(pugi::xml_node&);
	virtual bool Save(pugi::xml_node&) const;

	void ChangeScene(int new_scene);
	Scene* current_scene = nullptr;
};
	
#endif // _SCENE_MANAGER_H_