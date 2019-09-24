StaticObject: .h, .cpp
======================

StaticObject is a class derived from :doc:`Object <object>`. It represents a mesh in 3D space and it
is used for non-animated and static meshes (not that there's much choice currently).
It does not store its vertex data, instead storing the data's positions in OpenGL buffers in a :doc:`MeshInVBOs <mesh>`.
This is done to reduce the overhead of uploading the data to OpenGL.

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

is called, StaticObject calculates all relevant data and calls the glDrawElementsBaseVertex function, drawing itself to the screen.

.. note:: You generally do not need to call this function directly; it is instead called when ``Renderer::renderFrame()`` gets called

Besides the MeshInVBOs, StaticObject stores a :doc:`Texture <../textures/texture>` object and the corresponding useDefaultTexure flag (set true to, obviously, use the default checkerboard texture).
Both the MeshInVBOs and Texture within a StaticObject can be get and set using:
::
	void setMesh(MeshInVBOs& mesh);
	Mesh mesh();

	void setTexture(Texture& tex);
	Texture texture();

.. note:: Currently, just one Texture can be used. Further down the line, the Materal class should be implemented, which will allow 
	  the user to use more than one Texture per StaticObject.

The StaticObject class has the ObjectType of "STATIC"

.. seealso:: :doc:`Renderer <../renderer>`

using namespace std;

class Cup {
	int fillCup(int i) {
		contents = i;

		return i;
	}

	int contents;
};
