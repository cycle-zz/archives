#!/bin/sh
OUT_TARG="../bin/visualizer.debug.app/Contents/MacOS/visualizer.debug.app"
[ -z "$BUILD_ROOT" ] || OUT_TARG="${BUILD_ROOT}/${OUT_TARG}"
[ "$OUT_TARG" = "../bin/visualizer.debug.app/Contents/MacOS/../bin/visualizer.debug.app/Contents/MacOS/visualizer.debug.app" ] || [ "$OUT_TARG" = "../bin/visualizer.debug.app/Contents/MacOS/visualizer.debug.app" ] || cp -r "$OUT_TARG" "../bin/visualizer.debug.app/Contents/MacOS/../bin/visualizer.debug.app/Contents/MacOS/visualizer.debug.app"
