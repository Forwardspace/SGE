Quick Start Guide
=================

First, install SGE using the intructions outlined in the Installation Guide.
Now you've got a functional and up-to-date version of SGE.

Example Code
------------

If you open the file "test.cpp", you'll see the ``main()`` function.
The code here sets up SGE by calling ``sge::Renderer::init(...)`` and creating a simple scene using physics and instancing.
It also enables the FPS camera to allow the player to move.

This demonstrates a very simple SGE program.

Details
-------

You may be wondering how to create your own games/programs.
First off, include the ``SGE.h`` header.

Everything SGE provides is placed in the aptly named ``sge`` namespace (except GUI, which is in the ``sgeui`` namespace).
Before using anything from those namespaces, call
::
	sge::Renderer::init(int w, int h, std::string title, bool fullscreen);

function, which will initialize SGE and open a window.

When creating 3D objects, (currently) you there are static and instanced objects: doc:`StaticObject <../classes/objects/staticobject>`, doc:`StaticInstancedObject <../classes/objects/staticinstancedobject>`

To create a :doc:`StaticObject <../classes/objects/staticobject>` from a file, call
::
	sge::StaticObject::StaticObject(fs::path filename);

	//eg.
	auto object = sge::StaticObject("path/to/file.obj");

This will load the model from ``filename`` and render it every frame.
Nearly all model formats are supported (through Assimp).

To create an instanced object (used when you have to render multiple identical objects), check out its documentation.

If you don't want an object to render, set the renderObject flag to false.
::
	someObject.renderObject = false;

Set it back to true if you want to render it again.

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

.. note:: If you want a simple FPS camera, you can enable it by calling:
	  ::
		sge::FPSCamera::enable();

Putting it all together, it could look something like:
::
	...
	sge::Renderer::init(1024, 768, "Exempli gratia", false);

	auto camera = sge::Camera();
	sge::Renderer::setCurrentCamera(camera);	

	auto myObject = sge::StaticObject("path/to/file.obj");
	
	while (true) {
		sge::Renderer::renderFrame();
	}
	...

.. seealso:: :doc:`Renderer <../classes/renderer>`