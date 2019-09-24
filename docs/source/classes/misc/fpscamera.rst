FPSCamera: .h, .cpp
===================

class FPSCameraController
-------------------------

This is a singleton class that, when activated, takes control of the current camera and
allows the player to control a first-person character with WASD, Shift, Ctrl and mouse.
It assumes a flat world with downward-facing gravity.

.. note:: For this reason, you will most likely need to write a new controller or modify this one for your games.
	  Feel free to use the source code of this one.

It also inits and uses a dynamic rigid body to interact with the physics world.

How to use it?
**************

The most important functions are
::
	void enable();	//Call to enable the controller
	void disable();	//Call to temporarily or permanently disable the controller

There are also some publicly configurable variables such as gravity or speed (check FPSCamera.h for info)