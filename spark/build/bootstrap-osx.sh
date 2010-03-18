#!/bin/bash

OUTPUT="spawner"

#
# Custom Include & Library Paths
#
INCPATH="/System/Library/Frameworks/OpenGL.framework/Headers /System/Library/Frameworks/GLUT.framework/Headers /usr/include /usr/local/include ../source"
LDLIBS="-lobjc -L/usr/X11R6/lib/  -lX11 -lXext -lXmu -lXt -lXi -lSM -lICE -lc"

#
# Create project files
#
qmake -project \
	TEMPLATE="app" \
	CONFIG+="debug opengl "\
	TARGET="$OUTPUT.debug" \
	DEFINES+="DEBUG" \
	DESTDIR="../bin" \
	INCLUDEPATH+="$INCPATH "\
	LIBS+="$LDLIBS $EXRLIBS"\
	../source/*.h ../source/*.cpp ../source/*.inc ../source/*.inl ../source/*.ui\
	-o debug-osx.pro

qmake -project \
	TEMPLATE="app"\
	CONFIG+="release opengl "\
	TARGET="$OUTPUT" \
	DESTDIR="../bin" \
	INCLUDEPATH+="$INCPATH "\
	LIBS+="$LDLIBS $EXRLIBS"\
	../source/*.h ../source/*.cpp ../source/*.inc ../source/*.inl ../source/*.ui\
	-o release-osx.pro

#
# Create Makefiles
#
qmake -makefile debug-osx.pro -o debug-osx.mk
qmake -makefile release-osx.pro -o release-osx.mk

#
# Setup for default build
#
cp release-osx.mk osx.mk

#
# Create XCode Projects
#
qmake -spec macx-pbuilder debug-osx.pro
qmake -spec macx-pbuilder release-osx.pro
