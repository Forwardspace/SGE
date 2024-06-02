Object: .h, .cpp
================

class Object
------------
The Object class is a base class for the :doc:`StaticObject <staticobject>` class, and contains all of the information needed to describe an object in 3D space, *minus the actual vertex data*.
The actual data is stored differently based on the object's type.

The class stores a 4x4 model matrix, which is recalculated when any of the Object's attributes are changed. The matrix is not available externally.
Any class deriving from Object must have a 
::
	void render();

function, which renders the object (currently) directly onto the screen. It is virtual in Object.

.. note:: Do not use the Object class directly; instead derive from it or store pointers to Objects.

namespace ObjectType
--------------------

Describes the type of an object.
The Object class has the ObjectType of "GENERIC"