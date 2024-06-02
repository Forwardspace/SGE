BufferManager: .h, .cpp
=======================

The BufferManager class provides an abstraction for access to OpenGL buffers.
It is used by objects to store vertex data inside of buffers (mostly VBOs).

It provides several functions, however none of which are useful if you're not
creating new renderable objects.

struct ...
----------

These are various structs describing the target buffers to modify and storing OpenGL buffer metadata.

class BufferManager
-------------------

How to use it?
==============

Bind a specific VAO with a custom ``id`` using:
::
	void bindVAO(unsigned int id);

to store the OpenGL state for later.

To add data to the buffer, use:
::
	BufferAppendResult appendToBuffer(BufferTargetDescriptor target, BufferDataDescriptor data);

This will return the position of the data in ``target``, which you can use later when rendering.

Finally, access a buffer using:
::
	GLuint getBuffer(BufferID bd);

Which will return the raw OpenGL handle of that buffer or create it if it doesn't exist.

Details
*******

All of these functions will create buffer objects if they don't yet exist, so you don't have to worry about instantiating them
Additionally, ``appendToBuffer`` will not only create a new buffer, but configure it as well, as long as the ``BufferSubtype`` is either ``VERTEX`` or
``TEXTURE``.