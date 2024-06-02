Texture: .h, .cpp
=================

The Texture class represents an image as used by OpenGL. It sends image data (either from a file loaded by DevIL or supplied by the user) 
to OpenGL and stores the OpenGL handle of the texture.

How to use it?
--------------

Create it either by using the contructor with a path:
::
	Texture::Texture(fs::path);

	//eg.
	auto myTex = sge::Texture("path/to/file");

(which will load the texture from the supplied file)
or the contructor with the raw pixel data:
::
	Texture(GLubyte* data, int w, int h, GLenum format);

	//eg.
	auto myTex = sge::Texture(myDataPtr, 512, 512, GL_RGB);

Which will load ``w * h * 3`` bytes from myDataPtr and send it to OpenGL with the format of ``format`` (for example ``GL_RGB`` or ``GL_BGR``).

Details
-------

Refer to the .cpp file (more specifically, ``void loadFromFile()`` and ``void makeTexture()``) to see how the textures are loaded from files or raw data.