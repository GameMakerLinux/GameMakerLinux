# Game Maker Linux

An attempt to have a Game Maker IDE on Linux.

## What is working?

* Opening a project
* Creating scripts and objects
* Editing scripts and objects
* Editing events scripts
* Visualisation of a room (showing/hiding layers and moving instances)

## TODO

* Add key names ("Key Press: Enter" instead of "Key Press: 13")
* Change events types
* Edition of sprites, sounds, etc.
* Saving
* Reorder the resources in the tree view via drag-and-drop
* Everything else...

## Things that will never be done

* Drag-and-Drop scripts
* Compilation (or maybe the same way GM:S does it for linux)
* Fonts
* Probably other things

## Compilation

### Prerequisites

* You need to build and install [Qutepart](https://github.com/andreikop/qutepart)
* You need a C++17 compiler

### Build

* Open in QtCreator
* Press "Build"

or

* `$ qmake && make`
