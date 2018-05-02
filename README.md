# Game Maker Linux

An attempt to have a Game Maker IDE on Linux.

## What is working?

* Opening a project
* Editing scripts
* Editing events scripts
* Visualisation of a room backgrounds
* Reorder the resources in the tree view via drag-and-drop (not saved)

## TODO

* Add key names ("Key Press: Enter" instead of "Key Press: 13")
* Add new events to objects
* Delete events from objects
* Change events types
* Save the reordering of the resources tree
* Edition of sprites, sounds, etc.
* Everything else...

## Things that will never be done

* Drag-and-Drop scripts
* Compilation (or maybe the same way GM:S does it for linux)
* Fonts
* Probably other things

## Compilation

### Prerequisites

* You need to build and install [QScintilla](https://riverbankcomputing.com/software/qscintilla/intro)
* You need a C++17 compiler (At least GCC 7)

It does compile with GCC 5 if you change the two `inline` variables and a variable using *Template argument deduction for class templates*.

### Build

* Open in QtCreator
* Press "Build"

or

* `$ qmake && make`
