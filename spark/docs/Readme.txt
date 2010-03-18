 -----------------------------------------------------------------
                         S P A R K
 -----------------------------------------------------------------
                        Version 1.0
	      Copyright 2004, Derek Gerstmann
	     email: dgerstma [AT] acm [DOT] org
 -----------------------------------------------------------------

DESCRIPTION:

SPARK is a basic stream processing abstraction and 
rendering toolkit for programmable graphics hardware that
I wrote as part of my Master's project at the NCCA at Bournemouth
University, UK during August/September of 2004.  

Development was done under Win32 using a GeForce 5900 SE with 
using v6.14.10.6176 of NVIDIA's display driver which 
supports GLSL.  Other platforms and graphics cards have
not been tested, but there should not be major issues.

The Linux and Mac ports both compile, but have not
been tested, due to the lack of capable graphics
hardware on the workstations that were available.

REQUIREMENTS:

The library is fairly useless without an NV30+ or Pixel 
Shader 2.0+ class graphics card which supports OpenGL 
Shading Language (GLSL).  

The bootrap scripts require Trolltech's qmake build system,
available from:

	http://www.trolltech.com.  
	
You'll also need the OpenGL Extension Wrangler toolkit
(GLEW), which you can obtain from:
	
	http://glew.sourceforge.net/

Finally, make sure that your graphics card driver supports
OpenGL Shading Language (GLSL), and that you have the
most recent version.

Download and install all packages.  The makefiles and
project files will probably need to be customized
for your installation.

COMPILING:

Makefiles are provided for both Linux and Mac OSX. Visual 
Studio .NET 2003 project files are included for Win32.

The build files will build the library, but require 
application code to be added in order to compile a 
useful binary.

Some file paths may need to be modified in order for everything
to compile (most likely the directories for the GLEW headers
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

This package includes several precompiled demo programs
for Win32 which can be found in the demos folder.

Source is included for the demos, but they were developed
with an earlier version of the library, so they may
not compile as is, but are included for completeness.

ACKNOWLEDGEMENTS:

Mark Harris and the GPGPU community for their groundbreaking
work on alternative uses of GPUs.

Ken Musgrave and Matthew Lewis for their insights 
and suggestions during the early stages of this project.

NCCA and Bournemouth University
