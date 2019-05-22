# ScapeGameEngine

### SGE version 0.1.0


ScapeGameEngine is a fully featured game engine, lacking, however, the ability to make any actual games with it.

### Features


However, here are the currently implemented
features:
- Mesh rendering
- Forward rendering
- Model loading (supports most formats through Assimp)
- Textures (through DevIL)
- The ability to make a static library

I am currently working on:
- User Input (almost there)
- GUI library (a bit further down the line)
- A functional editor (don't hold your breath)

### Compilation


SGE was made to be developed and compiled in Visual Studio.
Therefore, once you have it installed, clone the repository
and open the .sln file in VS.
From there, just make sure you're in the Debug x64 profile
and build the project.

This will, however, build SGE as a *standalone program*.
If you want to build it as a static library, run the
`setupAsLib.bat` script. This will automaticall make it compile
into `ScapeGameEngine.lib`.
You can change it back to compiling a standalone program by 
running `setupAsApp.bat`.
