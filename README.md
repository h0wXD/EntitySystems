## Experimental Entity (Component) System

Written in C++.

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

#### Windows

Microsoft Visual Studio 2013 or up is required for C++11 support. (Tested with 2013)

1. Download and install CMake version 3.2.1 or higher. http://www.cmake.org/
2. Open CMake and configure the directories:
* Source Code: EntitySystems
* Binaries: EntitySystems/Build
3. Configure and select MSMicroso Visual Studio
4. Generate
5. Go to the binaries folder and open the generated Solution file.
6. Build.

#### Linux

Latest GNU C Compiler or up is required for C++11 support. (Tested with 4.8.2)

1. Download and install CMake 3.2.1 or higher. (see below)
2. git clone https://github.com/h0wXD/EntitySystems.git
3. cd EntitySystems
4. mkdir build && cd build
5. cmake -DCMAKE_BUILD_TYPE=Release ..
6. make

##### Building CMake on Linux
1. Get the Unix/Linux Source download link. http://www.cmake.org/download/
2. wget http://www.cmake.org/files/v3.2/cmake-3.2.1.tar.gz
3. tar -xzvf cmake-3.2.1.tar.gz
4. cd cmake-3.2.1
5. ./bootstrap
6. make && sudo make install
