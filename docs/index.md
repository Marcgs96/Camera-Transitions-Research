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

### The SceneManager

### The TransitionManager

### The Transitions
