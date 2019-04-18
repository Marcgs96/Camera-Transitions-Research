#include <iostream> 
#include <sstream> 

#include "p2Defs.h"
#include "p2Log.h"

#include "Window.h"
#include "Input.h"
#include "Render.h"
#include "Textures.h"
#include "Audio.h"
#include "SceneManager.h"
#include "Map.h"
#include "TransitionManager.h"
#include "j1App.h"

// Constructor
j1App::j1App(int argc, char* args[]) : argc(argc), args(args)
{
	frames = 0;
	want_to_save = want_to_load = false;

	input = new Input();
	win = new Window();
	render = new Render();
	tex = new Textures();
	audio = new Audio();
	scene_manager = new SceneManager();
	map = new Map();
	transition_manager = new TransitionManager();

	// Ordered for awake / Start / Update
	// Reverse order of CleanUp
	AddModule(input);
	AddModule(win);
	AddModule(tex);
	AddModule(audio);
	AddModule(map);
	AddModule(scene_manager);
	AddModule(transition_manager);

	// render last to swap buffer
	AddModule(render);
}

// Destructor
j1App::~j1App()
{
	// release modules
	std::list<Module*>::reverse_iterator item = modules.rbegin();

	while(item != modules.rend())
	{
		RELEASE(*item);
		++item;
	}

	modules.clear();
}

void j1App::AddModule(Module* module)
{
	module->Init();
	modules.push_back(module);
}

// Called before render is available
bool j1App::Awake()
{
	pugi::xml_document	config_file;
	pugi::xml_node		config;
	pugi::xml_node		app_config;

	bool ret = false;
		
	config = LoadConfig(config_file);

	if(config.empty() == false)
	{
		// self-config
		ret = true;
		app_config = config.child("app");
		title = app_config.child("title").child_value();
		organization = app_config.child("organization").child_value();
		frame_rate = app_config.attribute("framerate_cap").as_uint();
	}

	if(ret == true)
	{
		std::list<Module*>::iterator item = modules.begin();

		while(item != modules.end() && ret == true)
		{
			ret = (*item)->Awake(config.child((*item)->name.c_str()));
			++item;
		}
	}

	return ret;
}

// Called before the first frame
bool j1App::Start()
{
	bool ret = true;
	std::list<Module*>::iterator item = modules.begin();

	while(item != modules.end() && ret == true)
	{
		ret = (*item)->Start();
		++item;
	}

	return ret;
}

// Called each loop iteration
bool j1App::Update()
{
	bool ret = true;
	PrepareUpdate();

	if(input->GetWindowEvent(WE_QUIT) == true)
		ret = false;

	if(ret == true)
		ret = PreUpdate();

	if(ret == true)
		ret = DoUpdate();

	if(ret == true)
		ret = PostUpdate();

	FinishUpdate();
	return ret;
}

// ---------------------------------------------
pugi::xml_node j1App::LoadConfig(pugi::xml_document& config_file) const
{
	pugi::xml_node ret;

	pugi::xml_parse_result result = config_file.load_file("config.xml");

	if(result == NULL)
		LOG("Could not load map xml file config.xml. pugi error: %s", result.description());
	else
		ret = config_file.child("config");

	return ret;
}

// ---------------------------------------------
void j1App::PrepareUpdate()
{
	last_sec_frame_count++;

	if (!paused)
	{
		dt = frame_time.ReadSec();
		if (dt > (float)frame_rate / 1000)
			dt = (float)frame_rate / 1000;
	}
	else
	{
		dt = 0;
	}
	frame_time.Start();
}

// ---------------------------------------------
void j1App::FinishUpdate()
{
	if(want_to_save == true)
		SavegameNow();

	if(want_to_load == true)
		LoadGameNow();

	if (last_sec_frame_time.Read() > 1000)
	{
		last_sec_frame_time.Start();
		prev_last_sec_frame_count = last_sec_frame_count;
		last_sec_frame_count = 0;
	}

	double last_frame_ms = frame_time.Read();
	uint32 frames_on_last_update = prev_last_sec_frame_count;

	static char title[256];
	sprintf_s(title, 256, " FPS: %i Last Frame Ms: %.2f",
		frames_on_last_update, last_frame_ms);
	App->win->SetTitle(title);


	if (frame_cap)
	{
		float waiting_time = (1000 / frame_rate);
		if (last_frame_ms < waiting_time)
		{
			waiting_time -= last_frame_ms;
			SDL_Delay(waiting_time);
		}		
	}
}

// Call modules before each loop iteration
bool j1App::PreUpdate()
{
	bool ret = true;
	
	Module* pModule = NULL;

	for(std::list<Module*>::iterator item = modules.begin(); item != modules.end() && ret == true; ++item)
	{
		pModule = *item;

		if(pModule->active == false) {
			continue;
		}

		ret = (*item)->PreUpdate();
	}

	return ret;
}

// Call modules on each loop iteration
bool j1App::DoUpdate()
{
	bool ret = true;

	Module* pModule = NULL;

	for(std::list<Module*>::iterator item = modules.begin(); item != modules.end() && ret == true; ++item)
	{
		pModule = *item;

		if(pModule->active == false) {
			continue;
		}

		ret = (*item)->Update(dt);
	}

	return ret;
}

// Call modules after each loop iteration
bool j1App::PostUpdate()
{
	bool ret = true;
	
	Module* pModule = NULL;

	for(std::list<Module*>::iterator item = modules.begin(); item != modules.end() && ret == true; ++item)
	{
		pModule = *item;

		if(pModule->active == false) {
			continue;
		}

		ret = (*item)->PostUpdate();
	}

	return ret;
}

// Called before quitting
bool j1App::CleanUp()
{
	bool ret = true;
	std::list<Module*>::reverse_iterator item = modules.rbegin();

	while(item != modules.rend() && ret == true)
	{
		ret = (*item)->CleanUp();
		++item;
	}

	return ret;
}

// ---------------------------------------
int j1App::GetArgc() const
{
	return argc;
}

// ---------------------------------------
const char* j1App::GetArgv(int index) const
{
	if(index < argc)
		return args[index];
	else
		return NULL;
}

// ---------------------------------------
const char* j1App::GetTitle() const
{
	return title.c_str();
}

// ---------------------------------------
const char* j1App::GetOrganization() const
{
	return organization.c_str();
}

// Load / Save
void j1App::LoadGame(const char* file)
{
	// we should be checking if that file actually exist
	// from the "GetSaveGames" list
	want_to_load = true;
	//load_game.create("%s%s", fs->GetSaveDirectory(), file);
}

// ---------------------------------------
void j1App::SaveGame(const char* file) const
{
	// we should be checking if that file actually exist
	// from the "GetSaveGames" list ... should we overwrite ?

	want_to_save = true;
	//save_game.create(file);
}

// ---------------------------------------
void j1App::GetSaveGames(std::list<std::string>& list_to_fill) const
{
	// need to add functionality to file_system module for this to work
}

bool j1App::LoadGameNow()
{
	bool ret = false;

	pugi::xml_document data;
	pugi::xml_node root;

	pugi::xml_parse_result result = data.load_file(load_game.c_str());

	if(result != NULL)
	{
		LOG("Loading new Game State from %s...", load_game.c_str());

		root = data.child("game_state");

		std::list<Module*>::iterator item = modules.begin();
		ret = true;

		while(item != modules.end() && ret == true)
		{
			ret = (*item)->Load(root.child((*item)->name.c_str()));
			++item;
		}

		data.reset();
		if(ret == true)
			LOG("...finished loading");
		else
			LOG("...loading process interrupted with error on module %s", (*item != NULL) ? (*item)->name.c_str(): "unknown");
	}
	else
		LOG("Could not parse game state xml file %s. pugi error: %s", load_game.c_str(), result.description());


	want_to_load = false;
	return ret;
}

bool j1App::SavegameNow() const
{
	bool ret = true;

	LOG("Saving Game State to %s...", save_game.c_str());

	// xml object were we will store all data
	pugi::xml_document data;
	pugi::xml_node root;
	
	root = data.append_child("game_state");

	std::list<Module*>::const_iterator item = modules.begin();

	while(item != modules.end() && ret == true)
	{
		ret = (*item)->Save(root.append_child((*item)->name.c_str()));
		++item;
	}

	if(ret == true)
	{
		data.save_file(save_game.c_str());
	
		LOG("... finished saving", save_game.c_str());
	}
	else
		LOG("Save process halted from an error in module %s", (*item != NULL) ? (*item)->name.c_str() : "unknown");

	data.reset();
	want_to_save = false;
	return ret;
}