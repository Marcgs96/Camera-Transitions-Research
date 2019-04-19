#ifndef _TRANSITION_MANAGER_H_
#define _TRANSITION_MANAGER_H_

//This is the module that Marc will do on his research?

#include "Module.h"
#include "Color.h"
#include "Transition.h"

class TransitionManager :
	public Module
{
public:


private:
	std::list<Transition*> active_transitions;

	//Util variables for diverse transitions
	SDL_Rect screen;


public:
	TransitionManager();
	~TransitionManager();

	// Called before render is available
	virtual bool Awake(pugi::xml_node&);
	// Called before the first frame
	virtual bool Start();
	// Called each loop iteration
	virtual bool PostUpdate();
	// Called before quitting
	virtual bool CleanUp();

	//--------------------------------

	void CreateFadeTransition(float transition_time, bool is_scene_change = false, int scene_to_transition = 0, Color color = Black);
	void CreateZoomTransition(float transition_time, float scale = 2);
	void CreateCameraTranslation(float transition_time, iPoint destination);
	void CreateWipeTransition(float transition_time, bool is_scene_change = false, int scene_to_transition = 0, Color color = Black);

	void DestroyTransition(Transition* transition_to_destroy);
};

#endif
