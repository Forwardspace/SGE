PackedTexture: .h, .cpp
=======================

namespace PackedTextureType
---------------------------

Defines the type of the texture inside a PackedTexture.
Feel free to extend this if you'd like more types.

class PackedTexture
-------------------

The PackedTexture class inherits from :doc:`Texture <texture>` and (along with the OpenGL handle stored by :doc:`Texture <texture>`)
stores a vector describing the layout of images stored one after the other in the texture.
It is mostly used by the SGE GUI system to store images for 3 different button states in one texture.

How to use it?
**************

Along with the texture file, you need to have a file with the same name and the *.csv* exstension.
This is a comma-separated values file in which you need to specify in what order are the images in the texture.

For example, if you have a file called *myTexture.png* in which the textures are (in order) normal, hover and clicked textures,
create the file *myTexture.csv*, inside which is:
::
	NORMAL, HOVER, CLICK

Then, simply supply the filename of the texture file to the contructor:
::
	PackedTexture::PackedTexture(fs::path filename);
	
	//eg.
	auto myTexture = sge::PackedTexture("path/to/file");

To access the individual texture coordinates, use:
::
	std::array<glm::vec2, 2> unpackTexture(PackedTextureType::Enum type);

	//eg.
	auto texCoords = myTexture.unpackTexture(PackedTextureType::HOVER);

which will return the texture coordinates (bottom left and upper right) of that specific texture.

.. note:: All of the images inside one texture file need to be of the same size and should preferably be power-of-two.

Details
*******

The function unpackTexture gets the index of the specific texture starting from 0 and the total number of textures
and then calculates the bounds as follows:
::
	bottomLeftBound = { index / totalNumberOfTextures, 0 }
	upperRightBound = { (index + 1) / totalNumberOfTextures, 0 }

.. note:: If no matching texture was found, it will return the coordinates of first texture.