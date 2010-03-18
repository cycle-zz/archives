#!/bin/bash

OUTPUT="visualizer"

#
# Custom Include & Library Paths
#
INCPATH="/System/Library/Frameworks/OpenGL.framework/Headers /System/Library/Frameworks/GLUT.framework/Headers /usr/include /usr/local/include ../source"
LDLIBS=" -L/usr/lib/ -framework OpenGL -framework GLUT -lobjc -L/usr/X11R6/lib/  -lX11 -lXext -lXmu -lXt -lXi -lSM -lICE"
EXRINC="/usr/local/include/OpenEXR/"
EXRLIBS="-L/usr/local/lib -lImath -lIlmImf -lHalf -lIex" 

#
# Remove existing files
#
rm *.pro
rm Makefile*

#
# Create project files
#
qmake -project \
	TEMPLATE="app" \
	CONFIG+="debug opengl "\
	TARGET="$OUTPUT.debug" \
	DEFINES+="DEBUG" \
	DESTDIR="../bin" \
	INCLUDEPATH+="$INCPATH $EXRINC"\
	LIBS+="$LDLIBS $EXRLIBS"\
	../source/*.h ../source/*.cpp ../source/*.inc ../source/*.inl ../source/*.ui\
	-o debug.pro

qmake -project \
	TEMPLATE="app"\
	CONFIG+="release opengl "\
	TARGET="$OUTPUT" \
	DESTDIR="../bin" \
	INCLUDEPATH+="$INCPATH $EXRINC"\
	LIBS+="$LDLIBS $EXRLIBS"\
	../source/*.h ../source/*.cpp ../source/*.inc ../source/*.inl ../source/*.ui\
	-o release.pro

#
# Create Makefiles
#
qmake -makefile debug.pro -o Makefile.debug
qmake -makefile release.pro -o Makefile.release

#
# Setup for debug build
#
qmake -spec macx-pbuilder debug.pro
cp Makefile.debug Makefile
