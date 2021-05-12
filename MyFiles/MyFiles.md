## MyFiles
This folder contains files that are not exactly part of the engine, but more like extension of the same. It also has the engine initialization in the main.

Other files are the the behaviors classes, that extend the class behavior. Those are for debugging, moving around the scene, testing the engine in general.

This folder can also work as example on how to use the engine.

Also I might replace the pre-compiled behaviors extensions for LUA scripts.

### Generating Makefiles
The generation of the makefiles is still a work on progress, but I am currently using premake. The GameEngine is also using premake, and both premake files from the engine and this folder works together to compile and link everything for you.

There are some requirements that has to be met:
- You need a pre-compiled static library of glfw on the folder ../thirdparty/GLFW, they provide one already compiled on their github.
- You need to have premake5 set up correctly on your computer.
- Have *make* available in your machine. You can use [chocalatey](https://community.chocolatey.org/packages/make) for this.

Since I am using mingw for the C++ compiler, you need to run:
> premake gmake2

I still can't guarantee if it works for visualstudio as well.

After that you can now make the executable by running make:
> make

If everything runs correctly it should have created a folder in MyFiles/bin/Debug where the executable is created.

You can also run this, for the O2 optimized version:
> make config=release

## Running the engine
You can either move all needed files to the MyFiles/bin/Debug folder or run the application directly from the MyFiles folder using the console.

The files currently needed for the engine to work are:
- Scene files: e.g. Scene1.sscene.json.
- Resources file: Resources.sres.json.
- resource folder: this contains images and shaders.




