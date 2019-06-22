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

class Mesh
----------

The Mesh class stores raw vertex data and is used in :doc:`StaticObject <staticobject>`.
Currently, Meshes store 3D vertex coordinates, 2D texture UV coordinates and 1D vertex coordinate indices.

How to use it?
**************

You generally don't need to deal with meshes directly; instead let the StaticObject class handle it.
Nevertheless, check out the .h file to see the various functions dealing with modifying various Mesh data - they're 
pretty self-explanatory.