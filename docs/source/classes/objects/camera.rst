Camera: .h, .cpp
================

The Camera class represents the viewer in 3D space, and serves as a storage for the 4 by 4 *view* matrix used when rendering.
As such, it only has functions modifying that matrix.

How to use it?
--------------

Construct the Camera and hold the reference to it as long as you want to use it:
::
	Camera::Camera();

	//eg.
	auto myCamera = sge::Camera();

Details
-------

Like the :doc:`Object <object>` class, it stores a 4 by 4 matrix and recalculates it only when the position, location or scale of the camera
has been modified.

To modify its position, location and scale, use:
::
	void setTransform(glm::vec3 pos, glm::vec3 rot, glm::vec3 scale);
	//or
	void setPos(float posX, float posY, float posZ);
	void setRot(float rotX, float rotY, float rotZ);

To get its position and rotation, use:
::
	glm::vec3 pos();
	glm::vec3 rot();