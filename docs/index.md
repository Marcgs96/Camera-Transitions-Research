## Camera Transitions

### What are camera transitions?

In films or videos, camera transitions are a post-production technique used to connect one shot with another. Simple enough, but what about video games?

Although the purpose is practically the same. In videogames, camera transitions won’t be a post-production technique, but a slice of code being executed seconds before - while - and after a scene change.
  
A camera transition can also be a smooth movement of the camera through the scene, without the need for a scene change.

### The reasons behind camera transitions

**Why don’t we use just a basic cut where one scene is instantly replaced by the next one?**

In cinema, there’s no problem using a basic cut, because there are no existing delays or freezes between the scene change. So filmmakers use complex or more artistic transitions most commonly to spice up the narrative or move backward or forward in time.

While in video games, when we change a scene, the game unloads the current scene and loads the entering scene information, making the game freeze for a small period of time. So if we don’t use any transition to ‘hide’ that freeze moment, the scene change will look really sketchy, poor or like a bug. Camera transitions are useful to tell the player; “ok, we are moving into another place of the game”.

Like in films, we also use camera transitions with a narrative or aesthetic background.

### Basic types of transitions

 - **Fade In/out**

A fade in is when the scene gradually turns to a single color, a fade out is exactly the opposite. Narratively, it often symbolizes the passage of time or signifies completion.

 - **Wipe**

A wipe is when a shot travels from one side of the frame to the other, replacing the previous scene. We can also see wipes where a black image comes from one side of the camera hiding the outgoing scene, then the black image returns to its original position giving a view to the incoming scene.

- **Dissolves**

A dissolve overlaps two shots or scenes, gradually transitioning from one to the other. This one is much more common in films and videos due it's complexity in videogames.

- **Zoom**

Zoom is when a camera shot that changes smoothly from a long shot to a close-up or vice versa.

### The use of shaders in camera transitions

A shader is a piece of code that is executed on the Graphics Processing Unit (GPU), usually found on a graphics card, to manipulate an image before it is drawn to the screen.

The use of shaders in camera transitions is very extended because it gives a lot of possibilities when creating a transition. I have not created any shader in my research because of its complexity and because it is not the focus of this research.

## My code implementation

I decided to keep both functionalities (change of scene and transition) separate to work independently and keep the code as encapsulated as possible, in addition to allowing me to make a greater diversity of types of transitions and the possibility of having multiple active transitions at the same time.

### The SceneManager

SceneManager is a module whose purpose is to control the behavior of the active scene and change the scene.

	enum SceneType{
		SCENE_01,
		SCENE_02
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
	
The Scene class is an abstract class from which the various scenes of the project will be inherited. 

    class Scene
	{
	public:
		Scene() {};
		~Scene() {};
		
		// Called before the first frame
		virtual bool Start() { return true; };

		// Called before all Updates
		virtual bool PreUpdate() { return true; };

		// Called each loop iteration
		virtual bool Update(float dt) { return true; };

		// Called before all Updates
		virtual bool PostUpdate() { return true; };

		// Called before quitting
		virtual bool CleanUp() { return true; };

		virtual bool Load(pugi::xml_node&) { return true; };

		virtual bool Save(pugi::xml_node&) const { return true; };
	};

### The TransitionManager

 TransitionManager is a module that consists of a factory of transitions. Contains a container with active transitions and updates the behavior of them, in addition to the methods of creation and destruction of these.

	class TransitionManager :
		public Module
	{
	private:
		std::list<Transition*> active_transitions;

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

		//-----Creation Methods-------

		void CreateFadeTransition(float transition_time, bool is_scene_change = false, int scene_to_transition = 0, Color color = Black);
		void CreateZoomTransition(float transition_time, float scale = 2);
		void CreateCameraTranslation(float transition_time, iPoint destination);
		void CreateBarsTransition(float transition_time, bool is_scene_change = false, int scene_to_transition = 0, bool horizontal = false, Color color = Black);
		void CreateWipeTransition(float transition_time, bool is_scene_change = false, int scene_to_transition = 0, Color color = Black);
		void CreateSquaresTransition(float transition_time, bool is_scene_change = false, int scene_to_transition = 0, Color color = Black);

		void DestroyTransition(Transition* transition_to_destroy);
		
		//-----Is there any active transition?
		bool transitioning = false;
	};

 
### The Transitions

