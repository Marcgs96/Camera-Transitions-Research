# Camera Transitions

## What are camera transitions?

In films or videos, camera transitions are a post-production technique used to connect one shot with another. Simple enough, but what about video games?

Although the purpose is practically the same. In videogames, camera transitions won’t be a post-production technique, but a slice of code being executed seconds before - while - and after a scene change.
  
A camera transition can also be a smooth movement of the camera through the scene, without the need for a scene change.

## The reasons behind camera transitions

**Why don’t we use just a basic cut where one scene is instantly replaced by the next one?**

In cinema, there’s no problem using a basic cut, because there are no existing delays or freezes between the scene change. So filmmakers use complex or more artistic transitions most commonly to spice up the narrative or move backward or forward in time.

While in video games, when we change a scene, the game unloads the current scene and loads the entering scene information, making the game even freeze for a small period of time. So if we don’t use any transition to ‘hide’ that procces, the scene change will look really sketchy, poor or like a bug. Camera transitions are useful to tell the player; “ok, we are moving into another place of the game”.

Like in films, we also use camera transitions with a narrative or aesthetic background.

## Basic types of transitions

### Basic types of transitions

  - **Fade In/out**

A fade in is when the scene gradually turns to a single color, a fade out is exactly the opposite. Narratively, it often symbolizes the passage of time or signifies completion.

![enter image description here](https://media.giphy.com/media/JUXanPn5SjGgNzn9lf/giphy.gif)

 - **Wipe**

A wipe is when a shot travels from one side of the frame to the other, replacing the previous scene. We can also see wipes where a black image comes from one side of the camera hiding the outgoing scene, then the black image returns to its original position giving a view to the incoming scene.

![enter image description here](https://media.giphy.com/media/XDdHENx4GgG9qiFMfu/giphy.gif)

- **Dissolves**

A dissolve overlaps two shots or scenes, gradually transitioning from one to the other.

![enter image description here](https://media.giphy.com/media/J6V3UX7i0MrpcCh4Gi/giphy.gif)

- **Zoom**

Zoom is when a camera shot that changes smoothly from a long shot to a close-up or vice versa.

![enter image description here](https://media.giphy.com/media/iDlcfvCMIQmqRpdkHy/giphy.gif)


## The use of shaders in camera transitions

A shader is a piece of code that is executed on the Graphics Processing Unit (GPU), usually found on a graphics card, to manipulate an image before it is drawn to the screen.

The use of shaders in camera transitions is very extended because it gives a lot of possibilities when creating a transition. I have not created any shader in my research because of its complexity and because it is not the focus of this research.

# My code implementation

I decided to keep both functionalities (change of scene and transition) separate to work independently and keep the code as encapsulated as possible, in addition to allowing me to make a greater diversity of types of transitions and the possibility of having multiple active transitions at the same time.

![core](https://github.com/Marcgs96/Camera-Transitions-Research/blob/master/docs/images/Core_implementation.png?raw=true)

## The SceneManager

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

## The TransitionManager

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

 
## The Transition

### **The concept**

When we talk about the basis of a transition, I propose this structure.

![enter image description here](https://github.com/Marcgs96/Camera-Transitions-Research/blob/master/docs/images/Transition_basic_structure.png?raw=true)

Where:

- **Entering** is the time before the scene change.
- **Action** is the frame of the scene change.
- **Exiting** is the time after the scene change.

So thats where the Transition abstract class come from.

	class Transition
	{
	private:
		enum class TransitionState {
			NONE,
			ENTERING, //Before the scene change
			ACTION, //The frame where the scene changes
			EXITING //After the Scene change
		};

	protected:
		TransitionState state;

		float transition_time; // total transition entering and exiting time
		Timer* current_time = nullptr; 

		float percent = 0; //percent of the current respect the total time. It goes from 0 to 1

	public:

		Transition(float transition_time);
		~Transition();

		void PostUpdate();

		//-----Update process-------

		virtual void Entering();
		virtual void Action();
		virtual void Exiting();

		float LerpValue(float percent, float start, float end);
	};

### **My transitions**

- **Fade**

[source code](https://github.com/Marcgs96/Camera-Transitions-Research/blob/master/Motor2D/Fade.cpp)

![enter image description here](https://media.giphy.com/media/AixqkUyJanbsY9VYb2/giphy.gif)
- **Dissolve**

![enter image description here](https://media.giphy.com/media/WUZUNcQWp2PTyrMtrn/giphy.gif)

- **Camera Translation with simple Lerp**

[source code](https://github.com/Marcgs96/Camera-Transitions-Research/blob/master/Motor2D/CameraTranslation.cpp)

![enter image description here](https://media.giphy.com/media/LkxcOAdzTRAtHkePoG/giphy.gif)

- **Wipe**

[source code](https://github.com/Marcgs96/Camera-Transitions-Research/blob/master/Motor2D/Wipe.cpp)

![enter image description here](https://media.giphy.com/media/VDe1FJ9MPiaI4TIort/giphy.gif)

- **Bars Wipe**

[source code](https://github.com/Marcgs96/Camera-Transitions-Research/blob/master/Motor2D/Bars.cpp)

![enter image description here](https://media.giphy.com/media/lNRNBH4jymoJ73muWK/giphy.gif)

- **Squares**

[source code](https://github.com/Marcgs96/Camera-Transitions-Research/blob/master/Motor2D/Squares.cpp)

![enter image description here](https://media.giphy.com/media/IbZjti8pOMMaRq3VOF/giphy.gif)

### TODO's

**Let's create a wipe transition where a rectangle slides in and out of the scene.**

**TODO 01**

Fill the method DrawRect().

![todo_01](https://github.com/Marcgs96/Camera-Transitions-Research/blob/master/docs/images/TODO_01.png?raw=true)

 - Solution
 
![todo_01_solution](https://github.com/Marcgs96/Camera-Transitions-Research/blob/master/docs/images/TODO_01_SOLUTION.png?raw=true)

**TODO 02**

Implement the Entering method of the wipe transition.

![todo_02](https://github.com/Marcgs96/Camera-Transitions-Research/blob/master/docs/images/TODO_02.png?raw=true)

- Solution

![todo_02_solution](https://github.com/Marcgs96/Camera-Transitions-Research/blob/master/docs/images/TODO_02_SOLUTION.png?raw=true)

**TODO 03**

Implement the Action method of the wipe transition.

![todo_03](https://github.com/Marcgs96/Camera-Transitions-Research/blob/master/docs/images/TODO_03.png?raw=true)


- Solution

![todo_03_solution](https://github.com/Marcgs96/Camera-Transitions-Research/blob/master/docs/images/TODO_03_SOLUTION.png?raw=true)

**TODO 04**

Implement the Exiting method of the wipe transition.

![todo_04](https://github.com/Marcgs96/Camera-Transitions-Research/blob/master/docs/images/TODO_04.png?raw=true)


- Solution

![todo_04_solution](https://github.com/Marcgs96/Camera-Transitions-Research/blob/master/docs/images/TODO_04_SOLUTION.png?raw=true)

**TODO 05**

Create a CreateWipeTransition method in your TransitionManager.

![todo_05_01](https://github.com/Marcgs96/Camera-Transitions-Research/blob/master/docs/images/TODO_05_01.png?raw=true)

![todo_05_02](https://github.com/Marcgs96/Camera-Transitions-Research/blob/master/docs/images/TODO_05_02.png?raw=true)

- Solution

![todo_05_solution_01](https://github.com/Marcgs96/Camera-Transitions-Research/blob/master/docs/images/TODO_05_SOLUTION_01.png?raw=true)

![todo_05_solution_02](https://github.com/Marcgs96/Camera-Transitions-Research/blob/master/docs/images/TODO_05_SOLUTION_02.png?raw=true)

**TODO 06**

Uncomment this code and introduce a case for your wipe transition! Try all transitions and choose one possible for your game or try design another one.

![todo_06](https://github.com/Marcgs96/Camera-Transitions-Research/blob/master/docs/images/TODO_06.png?raw=true)


- Solution

![todo_06_solution](https://github.com/Marcgs96/Camera-Transitions-Research/blob/master/docs/images/TODO_06_SOLUTION.png?raw=true)

### Reference Links

**About video transitions**

- [Link 1](https://biteable.com/blog/tips/video-transitions-effects-examples/)
- [Link 2](http://www.davetech.co.uk/screentransitions)

**About Shaders**
 - [Link](https://www.webopedia.com/TERM/S/shader.html)

**Fan collection of transitions**

- [Link](http://www.davetech.co.uk/screentransitions)



