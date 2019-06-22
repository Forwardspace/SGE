Quick Start Guide
=================

If you're here, that means you've beaten the remarkable odds of not actually being interested in this project. Congratulations.
Now, let's get started.

First, install SGE using the intructions outlined in the Installation Guide.
Now you've got a functional and up-to-date version of SGE.

Example Code
------------

If you open the file "test.cpp", you'll see the ``main()`` function.
The code here sets up SGE by calling ``sge::Renderer::init(...)`` and creating two :doc:`StaticObjects <../classes/objects/staticobject>`. It then sets their position and rotation.
It creates a :doc:`ShaderProgram <../classes/shaders/shaderprogram>`, before finally creating a wooden :doc:`Texture <../classes/textures/texture>` and assigning it to the two Objects.

(currently, there is also some GUI code here; the GUI is in development - you can ignore it for now)

This demonstrates a very simple program.
If you want more details, carry on reading.

Details
-------

You may be wondering how to create your own games/programs.
First off, include the ``SGE.h`` header.

Everything SGE provides is placed in the aptly named ``sge`` namespace (except GUI, which is in the ``sgeui`` namespace).
Before using anything from those namespaces, call
::
	sge::Renderer::init(int w, int h, std::string title, bool fullscreen);

function, which will initialize SGE and open a window.

When creating 3D objects, (currently) you have only one option: :doc:`StaticObject <../classes/objects/staticobject>`.
To create a :doc:`StaticObject <../classes/objects/staticobject>` from a file, call
::
	sge::StaticObject::StaticObject(fs::path filename);

	//eg.
	auto object = sge::StaticObject("path/to/file.obj");

This will load the model from ``filename`` and prepare it for rendering.

:doc:`StaticObject <../classes/objects/staticobject>` supports model loading through Assimp - therefore supporting most model file formats.
Ones tested by me are .obj and .fbx.

If you don't want an object to render, set the renderObject flag to false.
::
	someObject.renderObject = false;

Set it back to true if you want to render it again.

.. note:: Before actually rendering anything, a shader program has to be created.
	  Check out the code in test.cpp to see how.

	  TODO: create a default ShaderProgram to allow users to skip this step

A :doc:`Camera <../classes/objects/camera>` has to be created to describe the positon and rotation of the viewer:
::
	sge::Camera::Camera();

	//eg.
	auto camera = sge::Camera();

The :doc:`Camera <../classes/objects/camera>` then has to be set as the current one in Renderer:
::
	sge::Renderer::setCurrentCamera(camera);

All done!
Now, in a loop, do:
::
	sge::Renderer::renderFrame();

.. note:: If you want a free-look FPS camera, you can enable it by calling:
	  ::
		sge::FPSCamera::enable();
		
		//Adjust the speed like this
		sge::FPSCamera::speed = someValue;

Putting it all together, it could look something like:
::
	...
	sge::Renderer::init(1024, 768, "Exempli gratia", false);

	//<Create shader program here>

	auto camera = sge::Camera();
	sge::Renderer::setCurrentCamera(camera);	

	auto myObject = sge::StaticObject("path/to/file.obj");
	
	while (true) {
		sge::Renderer::renderFrame();
	}
	...

.. seealso:: :doc:`Renderer <../classes/renderer>`