######################################################################
# Automatically generated by qmake (1.05a) Thu Jun 17 17:06:33 2004
######################################################################

QMAKE_CXXFLAGS_DEBUG+=-fexceptions
TEMPLATE=app
CONFIG+=debug opengl 
TARGET=visualizer.debug
DEFINES+=DEBUG
DESTDIR=../bin
INCLUDEPATH+=/usr/include ../source/ /mahome/c1405511/software/openexr/include/OpenEXR
LIBS+=-L/usr/X11R6/lib/ -lX11 -lXext -lXmu -lXt -lXi -lSM -lICE -lglut -lGL -lGLU  -L/mahome/c1405511/software/openexr/lib -lImath -lIlmImf -lHalf -lIex
TEMPLATE = app
DEPENDPATH += ../source \
              ../source \
              ../source \
              ../source \
              ../source \
              ../source \
              ../source \
              ../source \
              ../source \
              ../source \
              ../source \
              ../source \
              ../source \
              ../source \
              ../source \
              ../source \
              ../source \
              ../source \
              ../source \
              ../source \
              ../source \
              ../source \
              ../source \
              ../source \
              ../source \
              ../source \
              ../source \
              ../source \
              ../source \
              ../source \
              ../source \
              ../source \
              ../source \
              ../source \
              ../source \
              ../source \
              ../source \
              ../source \
              ../source \
              ../source \
              ../source \
              ../source \
              ../source \
              ../source \
              ../source \
              ../source \
              ../source \
              ../source
INCLUDEPATH += . ../source

# Input
HEADERS += ../source/Camera.h \
           ../source/Color.h \
           ../source/CubeTables.h \
           ../source/DataTypes.h \
           ../source/GlutHeaders.h \
           ../source/GlutKeyBindings.h \
           ../source/Hypertexture.h \
           ../source/Image.h \
           ../source/Implicits.h \
           ../source/KeyBindings.h \
           ../source/Maths.h \
           ../source/Matrix.h \
           ../source/Messages.h \
           ../source/OpenGLHeaders.h \
           ../source/Operators.h \
           ../source/Polygonizer.h \
           ../source/Procedural.h \
           ../source/Random.h \
           ../source/RandTables.h \
           ../source/RayTracer.h \
           ../source/Set.h \
           ../source/Shading.h \
           ../source/Timer.h \
           ../source/Transform.h \
           ../source/Vector.h \
           ../source/Visualizer.h \
           ../source/Volumes.h \
           ../source/Window.h
SOURCES += ../source/Camera.cpp \
           ../source/Color.cpp \
           ../source/GlutWindow.cpp \
           ../source/Hypertexture.cpp \
           ../source/Image.cpp \
           ../source/Implicits.cpp \
           ../source/Maths.cpp \
           ../source/Matrix.cpp \
           ../source/Messages.cpp \
           ../source/Polygonizer.cpp \
           ../source/Procedural.cpp \
           ../source/Random.cpp \
           ../source/RayTracer.cpp \
           ../source/Set.cpp \
           ../source/Shading.cpp \
           ../source/Timer.cpp \
           ../source/Transform.cpp \
           ../source/Vector.cpp \
           ../source/Visualizer.cpp \
           ../source/Window.cpp
