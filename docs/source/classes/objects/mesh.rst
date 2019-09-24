Mesh: .h, .cpp
==============

struct Vertex3D
---------------

Stores one 3D coordinate.
Has functions to convert from other representations of coordinates to this one.

It is equivalent to 3 side-by-side floats (12 bytes).

struct Vertex2D
---------------

Stores one 2D coordinate.
Also has functions to convert from other representations of coordinates to this one.

It is equivalent to 2 side-by-side floats (8 bytes).

struct MeshInVBOs
-----------------
This class does not store any vertex data on its own. Instead, it stores the position and size of the vertex attributes
that have been moved over to OpenGL buffers.
This way saves a significant amount of memory and increases performance.

class Mesh
----------

The Mesh class stores raw vertex data and is used in :doc:`StaticObject <staticobject>`.
Currently, Meshes store 3D vertex coordinates, 2D texture UV coordinates and 1D vertex coordinate indices.

How to use it?
**************

You generally don't need to deal with meshes directly; instead let the StaticObject class handle it.
Nevertheless, check out the .h file to see the various functions dealing with modifying various Mesh data - they're 
pretty self-explanatory.

A notable function is the
::
	MeshInVBOs moveToVBOs(BufferTargetDescriptor target);

function, which moves the mesh data to VBOs marked with ``target`` and returns a MeshInVBOs object so the caller can use the data.
Unless you want to have easy access to the data, use this function to improve performance

.. note:: The ``moveToVBos`` function does not invalidate the data in the Mesh, and thus can be called multiple times, producing copies
	  of the data stored separately in VBOs.