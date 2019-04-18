#ifndef _j1App_H_
#define _j1App_H_

#include <list>
#include <vector>

#include "Timer.h"
#include "PerfTimer.h"
#include "Module.h"
#include "PugiXml\src\pugixml.hpp"

// Modules
class Window;
class Input;
class Render;
class Textures;
class Audio;
class SceneManager;
class Map;
class TransitionManager;

class j1App
{
public:

	// Constructor
	j1App(int argc, char* args[]);

	// Destructor
	virtual ~j1App();

	// Called before render is available
	bool Awake();

	// Called before the first frame
	bool Start();

	// Called each loop iteration
	bool Update();

	// Called before quitting
	bool CleanUp();

	// Add a new module to handle
	void AddModule(Module* module);

	// Exposing some properties for reading
	int GetArgc() const;
	const char* GetArgv(int index) const;
	const char* GetTitle() const;
	const char* GetOrganization() const;

	void LoadGame(const char* file);
	void SaveGame(const char* file) const;
	void GetSaveGames(std::list<std::string>& list_to_fill) const;

private:

	// Load config file
	pugi::xml_node LoadConfig(pugi::xml_document&) const;

	// Call modules before each loop iteration
	void PrepareUpdate();

	// Call modules before each loop iteration
	void FinishUpdate();

	// Call modules before each loop iteration
	bool PreUpdate();

	// Call modules on each loop iteration
	bool DoUpdate();

	// Call modules after each loop iteration
	bool PostUpdate();

	// Load / Save
	bool LoadGameNow();
	bool SavegameNow() const;

public:

	// Modules
	Window*			win;
	Input*			input;
	Render*			render;
	Textures*		tex;
	Audio*			audio;
	SceneManager*	scene_manager;
	Map*			map;
	TransitionManager* transition_manager;

private:

	std::list<Module*>	modules;
	uint				frames;
	float				dt;
	int					argc;
	char**				args;

	Timer				frame_time;
	double				frame_rate;
	bool				paused = false;
	bool				frame_cap = true;
	Timer				last_sec_frame_time;
	uint32				last_sec_frame_count = 0;
	uint32				prev_last_sec_frame_count = 0;

	std::string			title;
	std::string			organization;

	mutable bool		want_to_save;
	bool				want_to_load;
	std::string			load_game;
	mutable std::string	save_game;
};

extern j1App* App;

#endif