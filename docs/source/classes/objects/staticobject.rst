StaticObject: .h, .cpp
======================

StaticObject is a class derived from Object. It is used primarily for non-animated meshes (not that there's much choice currently).
It stores its vertex data in a *Mesh*.

When the function
::
	void render();

is called, StaticObject obtains the model, view and projection matrices from itself, the current Camera and the Renderer class.