Renderer: .h, .cpp
==================================

Usage
-----

Renderer is a singleton class that manages the (as the name implies) rendering of frames to the screen.
As such, it is also the main class that initializes and terminates other SGE modules.

.. note:: Before any SGE modules, classes, functions or systems can be used, initialize SGE by calling:
	  ::
	  	static void Renderer::init(w, h, std::string name, bool fullscreen);

	  This opens a window of *w* by *h* pixels with the title *name*. If *fullscreen* is true, the window will be fullscreen.
	  It then initializes all other SGE systems.

	  SGE uses GLFW as the window and input library of choice and GLAD as the OpenGL extension loader.
	  DevIL is used for loading images and Assimp for loading models.
	  Those libraries are also initialized here.


Before exiting, call:
::
	static void Renderer::terminate(bool exit = true);

Which will exit the program unless exit is false.

Rendering
*********

When all the setup is done for any one frame, the function
::
	static void Renderer::renderFrame();

will take over and render that frame, as well as update the GUI and all other systems

The pair
::
	static void Renderer::updateProjectionMatrix(float FoV, float NCP, float FCP);
	static glm::mat4x4 sge::Renderer::projectionMatrix();

(where NCP = near clipping plane and FCP = far clipping plane) will update and return the projection matrix, respectfully.

The pair
::
	static void Renderer::setCurrentCamera(Camera* cam);
	static Camera* sge::Renderer::currentCamera();

set and get the :doc:`Camera <objects/camera>` used for rendering frames.  

Callbacks
*********

Renderer also deals with callbacks; they are called after each frame.
These functions allow you to add and remove callbacks, respectively
::
	static void Renderer::registerWindowCallback(std::function<void()>);
	static void Renderer::removeWindowCallback(std::function<void()>);

They are used mainly to handle window events.

Internal
********

The function
::
	static GLFWwindow* sge::Renderer::wind();

Returns the GLFW window and is generally only used internally.
The same is true of
::
	static void sge::Renderer::registerObject();
	static void sge::Renderer::removeObject();

which register and remove the object from being drawn automatically every frame.