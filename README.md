ViewpointCursor
===============

Sample implementation of Viewpoint Cursor.

** Please note that this implementation is currently broken. I'm in the process
of tidying up my original research code, hopefully done in the next day or two.
**


## Introduction

ViewpointCursor is a technique for mapping 2D user input to 3D, multi-projector
Spatial Augmented Reality systems. At its heart, ViewpointCursor is ray-based
selection, but does a few tricks to handle the limitation of projectors. In
particular:

1. VP does away with the system cursor all together. The system cursor is
   useless in SAR, because the standard left-right mapping of cursors to
   monitors doesn't work when you have projectors in all kinds of positions and
   orientations.

1. VP maps 2D input to a virtual plane in front of the user. This makes input
   make sense. Left is always left, up is always up, from the user's point of
   view.

1. Whilst input is mapped to 2D, the cursor itself is placed as a 3D object in
   the scene. The cursor appears at the correct spot regardless of projector
   placement. 

1. The 3D cursor only moves when the user provides input. This keeps the cursor
   stable when viewing, allowing users to move around without the cursor going
   crazy.

1. Reverse updates are performed whenever the user's point of view changes.
   This stops the cursor jumping around unexpectedly.


## Installation
Run:

```
./configure
make
make install
```

You can use pkg-config to configure include paths and linker flags.

Not into autotools? Just copy the source files into your project.

### Dependencies
It's just C++. VP was originally implemented for Linux, but has also been
tested on OSX. I don't do any crazy cross-platform stuff, so it should work on
Windows.

VP requires the following libraries:

* GLM (http://http://glm.g-truc.net/)
* OpenGL, GLUT (for demo app)

## Usage

More to come...

