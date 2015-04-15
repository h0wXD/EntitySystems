## Experimental Entity (Component) System

Written in C++.  
**Very early in development stages**
*****

### Introduction

This repository is meant to be a playground to experiment and try to create a proper highly performant and yet easy to use entity system.

### Goals

* High performance
* Versatility
* Easily parallelizable
* Easy to read
* Easy to write
* Avoid low-level memory access and management
* Fully C++11 compliant

### Description

Like most entity systems, entities will only exist as a collection of their components. All components will be data-only, they will have no behavior. Unlike most entity systems one type of component will not be handled by one single system, instead systems will have collections of one or more types of components. The collection of components will be passed to and processed by stateless managers. These stateless managers should make it obvious what components directly depend on eachother and which ones don't, making it easy to run them in parallel.

When a component has to be referenced by a system that does not own the component a Handle can be used; handles will expire after the processing has been done. A Reference will remain valid for the lifetime of the object but will be more expensive to use.

### Notes

This will most likely end up as a tiny library of helper methods and classes as the optimal solution isn't the most general one.

At the moment a System only supports up to 32,566 entities due to implementation details. In the future different kinds will be added for huge datasets.

This project makes heavy use of templates, compilation time will probably not be great.

### Building EntitySystems

Download and install CMake version 2.6 or higher. http://www.cmake.org/
There's a guide below on how to build CMake on Linux if necessary.

#### Windows

Microsoft Visual Studio 2013 or up is required for C++11 support. (Tested with 2013)

1. Open CMake and configure the directories:
  * Source Code: EntitySystems
  * Binaries: EntitySystems/Build
2. Configure and select Microsoft Visual Studio
3. Uncheck BUILD_TEST_GAME.
4. Generate
5. Go to the binaries folder and open the generated Solution file.
6. Build.

#### Linux

Latest GNU C Compiler or up is required for C++11 support. (Tested with 4.8.2)

1. git clone https://github.com/h0wXD/EntitySystems.git
2. cd EntitySystems
3. mkdir build && cd build
4. cmake -DCMAKE_BUILD_TYPE=Release ..
5. make

##### Building CMake on Linux
1. Get the Unix/Linux Source download link. http://www.cmake.org/download/
2. wget http://www.cmake.org/files/v3.2/cmake-3.2.1.tar.gz
3. tar -xzvf cmake-3.2.1.tar.gz
4. cd cmake-3.2.1
5. ./bootstrap
6. make && sudo make install

### Building TestGame with EntitySystems

#### Windows

1. Open the folder EntitySystems/Lib.
2. Download and unzip glew (zip). http://glew.sourceforge.net/
3. Clone glfw (git clone). https://github.com/glfw/glfw
4. Download and unzip oglplus. http://oglplus.org/
5. Make sure you have a similar directory structure:
  * Lib\
  ***** glew-1.12.0
  ***** glfw-3.1.1
  ***** oglplus-0.60.0
6. Run cmake, tick advanced options, and make sure paths to the libraries are correct.
7. Build glew (see below).
8. Build oglfw (see below).
9. Open CMake and configure the directories:
  * Source Code: EntitySystems
  * Binaries: EntitySystems/Build
10. Configure and select Microsoft Visual Studio
11. Check BUILD_TEST_GAME.
12. Generate
13. Go to the binaries folder and open the generated Solution file.
14. Build.

##### Building glew

###### Windows

1. Navigate to glew-x.x.x\build\vc12 and open glew.sln
2. Build glew_shared
3. Don't forget to move glew32.dll into the same folder as TestGame.exe.

###### Linux

1. cd glew-x.x.x
2. make && sudo make install

##### Building glfw

###### Windows

1. Open CMake and configure the directories:
  * Source Code: EntitySystems/Lib/glfw-x.x.x
  * Binaries: EntitySystems/Lib/glfw-x.x.x/Build
2. Configure and select Microsoft Visual Studio
3. Generate
4. Go to the binaries folder and open the generated Solution file.
5. Build.

###### Linux

1. TODO
