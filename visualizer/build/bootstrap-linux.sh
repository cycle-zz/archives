#!/bin/bash

OUTPUT="visualizer"

#
# Custom Include & Library Paths
#
INCPATH="/usr/include ../source/"
LDLIBS="-L/usr/X11R6/lib/ -lX11 -lXext -lXmu -lXt -lXi -lSM -lICE -lglut -lGL -lGLU "
EXRINC="/mahome/c1405511/software/openexr/include/OpenEXR"
EXRLIBS="-L/mahome/c1405511/software/openexr/lib -lImath -lIlmImf -lHalf -lIex"

#
# Create project files
#
qmake -project QMAKE_CXXFLAGS_DEBUG+="-fexceptions"\
	TEMPLATE="app" \
	CONFIG+="debug opengl "\
	TARGET="$OUTPUT.debug" \
	DEFINES+="DEBUG" \
	DESTDIR="../bin" \
	INCLUDEPATH+="$INCPATH $EXRINC"\
	LIBS+="$LDLIBS $EXRLIBS"\
	../source/*.h ../source/*.cpp ../source/*.inc ../source/*.inl ../source/*.ui\
	-o debug-linux.pro

qmake -project QMAKE_CXXFLAGS_RELEASE="-fexceptions"\
	TEMPLATE="app"\
	CONFIG+="release opengl "\
	TARGET="$OUTPUT" \
	DESTDIR="../bin" \
	INCLUDEPATH+="$INCPATH $EXRINC"\
	LIBS+="$LDLIBS $EXRLIBS"\
	../source/*.h ../source/*.cpp ../source/*.inc ../source/*.inl ../source/*.ui\
	-o release-linux.pro

#
# Create Makefiles
#
qmake -makefile debug-linux.pro -o debug-linux.mk
qmake -makefile release-linux.pro -o release-linux.mk

#
# Setup for default build
#
cp release-linux.mk linux.mk
