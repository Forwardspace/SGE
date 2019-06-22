StaticObject: .h, .cpp
======================

StaticObject is a class derived from :doc:`Object <object>`. It represents a mesh in 3D space and it
is used for non-animated meshes (not that there's much choice currently).
It stores its vertex data in a :doc:`Mesh <mesh>`.

How to use it?
--------------

When you create a StaticObject and until you stop keeping a refrence to it, it will automatically be drawn to the screen each frame
(unless the renderObject flag is false).
Therefore, all that is needed is to construct the StaticObject using
::
	StaticObject::StaticObject(fs::path path);

	//eg.
	auto myObject = sge::StaticObject("path/to/file");

Details
-------

When the function
::
	void render();

is called, StaticObject calculates all relevant data and uploads the neccessary info to OpenGL and the shader, drawing itself to the screen.

.. note:: You generally do not need to call this function directly; it is instead called when ``Renderer::renderFrame()`` gets called

Besides the Mesh, StaticObject stores a :doc:`Texture <../textures/texture>` object and the corresponding useDefaultTexure flag (set true to, obviously, use the default checkerboard texture).
Both the Mesh and Texture within a StaticObject can be get and set using:
::
	void setMesh(Mesh& mesh);
	Mesh mesh();

	void setTexture(Texture& tex);
	Texture texture();

.. note:: Currently, just one Texture can be used. Further down the line, the Materal class should be implemented, which will allow 
	  the user to use more than one Texture per StaticObject.

The StaticObject class has the ObjectType of "STATIC"

.. seealso:: :doc:`Renderer <../renderer>`