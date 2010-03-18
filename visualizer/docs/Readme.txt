 -----------------------------------------------------------------
                     V I S U A L I Z E R
 -----------------------------------------------------------------
                        Version 1.0
	      Copyright 2004, Derek Gerstmann
 -----------------------------------------------------------------

DESCRIPTION:

Visualizer is a basic implicit rendering framework that I wrote
as part of a programming project at the NCCA at Bournemouth
University, UK during May/June of 2004.  It uses several
different methods to visualize a scalar implicit function.

FEATURES:

Polygonization
- Marching Cubes
- Marching Tetra
Ray Tracing
- Simple scanline based
Ray Marching
- Hypertexture

REQUIREMENTS:

The bootrap scripts require Trolltech's qmake build system,
available from www.trolltech.com.  Download and install
if you need to regenerate the Makefiles (probably not).

COMPILING:

Makefiles are provided for both linux and mac osx.

Some file paths may need to be modified in order for everything
to compile (most likely the directories for the OpenEXR headers
and libraries).

The correct paths can be specified by editing the
appropriate .mk files for your system (eg osx.mk, linux.mk)
located in the build folder, *or* by editing the bootstrap
shell scripts and executing them to generate the makefiles
(requires qmake).

Once you've finished making changes to the Makefiles or
bootstrap shell scripts, change to the build folder and select
the appropriate make file for your system.

OSX:

> cd build
> make -f osx.mk

Linux:

> cd build
> make -f linux.mk

RUNNING:

Simply evoke Visualizer from the command line.

> ./visualizer

ACKNOWLEDGEMENTS:

Jules Bloomenthal, and Paul Bourke for implementation details
for the polygonization algorithms.

Ken Perlin, Eric Heffert and Larry Gritz for implementation
details on ray tracing and ray marching hypertexture.

NCCA and Bournemouth University
