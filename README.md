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

### Description

Like most entity systems, entities will only exist as a collection of their components. All components will be data-only, they will have no behavior. Unlike most entity systems one type of component will not be handled by one single system, instead systems will have collections of one or more types of components. The collection of components will be passed to and processed by stateless managers. These stateless managers should make it obvious what components directly depend on eachother and which ones don't, making it easy to run them in parallel.

When a component has to be referenced by a system that does not own the component a Handle can be used; handles will expire after the processing has been done. A Reference will remain valid for the lifetime of the object but will be more expensive to use.
