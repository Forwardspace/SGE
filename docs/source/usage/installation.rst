Installation guide
==================

Although SGE (ScapeGameEngine) hasn't been optimised for installation
on every, or indeed any, device, it is possible.

Prerequisites
-------------

- Visual Studio 2019 (any edition)
- Windows, obviously
- An internet connection
- That's theoretically it

Installation Procedure, seriously, why are you trying to install this??
-----------------------------------------------------------------------

1. Begin by cloning the SGE repository from GitHub (https://www.github.com/Forwardspace/SGE)
2. Go to https://glad.dav1d.de/ (GLAD homepage) and set the gl API version to the latest value
3. Check "Generate a loader", "Generate" and dowload glad.zip, extract it in SGE/packages/
4. (important) Drag the glad.c file to the "Source files" folder in Visual Studio to add it to the project
5. Configure Bullet Physics, build LinearMath, BulletCollision, BulletDynamics and BulletSoftBody
6. Copy the built libraries in a new folder called "lib" under "bullet3".
7. Copy the "src" directory from the bullet source to the previously created "bullet3"
8. Open the .sln file in Visual Studio
9. Click Build > Build all and wait

You've now got an up-to-date version of SGE. Why are you torturing yourself???
You can edit the source code or run the program using the button "Local Windows Debugger".
When you're ready, continue to the Quick Start Guide.