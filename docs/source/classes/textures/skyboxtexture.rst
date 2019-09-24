SkyboxTexture: .h, .cpp
=======================

SkyboxTexture holds 8 individual OpenGL textures that can be rendered to a cube to give
the illusion of a sky or background.

How to use it?
--------------

Construct the SkyboxTexture by supplying it with a path:
::
	SkyboxTexture::SkyboxTexture(fs::path);

	//eg.
	auto mySkybox = sge::SkyboxTexture("path/to/file");

Then, set the skybox to render every frame by calling (e.g.):
::
	sge::Renderer::setCurrentSkyboxTex(&mySkybox);

Details
-------

Skybox format
*************

A skybox is composed of 6 image files with the same base and file type, but ending with
``_bk, _ft, _lf, _rt, _up, _dn`` (back, front, left, right, up and down textures, respectively).
The path supplied to SkyboxTexture constructor does not include any of those extensions.

For example, if you have files named ``.\\miramar_bk.png, .\\miramar_up.png, ...``, supply the path ``".\\miramar.png"``
to the constructor

Internal texture loading
************************

Internally, the 6 textures are loaded similarily to the normal Texture class.

Rendering
*********

Skyboxes generate a new VAO with the ID of 1001 and configure one attrib. array for storing the vertices of a cube.
They also compile a custom shader.