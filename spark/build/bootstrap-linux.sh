#!/bin/bash

OUTPUT="spark"

#
# Custom Include & Library Paths
#
GLEWPATH="/mahome/c1405511/software/glew"
GLEWINC="$GLEWPATH/include"
GLEWLIB="$GLEWPATH/lib"

INCPATH="/usr/include ../source/ $GLEWINC"
LDLIBS="-L/usr/X11R6/lib/ -lX11 -lXext -lXmu -lXt -lXi -lSM -lICE -lglut -L$GLEWLIB -lGLEW"

#
# Create project files
#
qmake -project QMAKE_CXXFLAGS_DEBUG+="-fexceptions"\
	TEMPLATE="app" \
	CONFIG+="debug opengl "\
	TARGET="$OUTPUT.debug" \
	DEFINES+="DEBUG" \
	DESTDIR="../bin" \
	INCLUDEPATH+="$INCPATH "\
	LIBS+="$LDLIBS $EXRLIBS"\
	../source/*.h ../source/*.cpp ../source/*.inc ../source/*.inl ../source/*.ui\
	-o debug-linux.pro

qmake -project QMAKE_CXXFLAGS_RELEASE="-fexceptions"\
	TEMPLATE="app"\
	CONFIG+="release opengl "\
	TARGET="$OUTPUT" \
	DESTDIR="../bin" \
	INCLUDEPATH+="$INCPATH "\
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
