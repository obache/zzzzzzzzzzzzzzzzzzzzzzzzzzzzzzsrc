$NetBSD: patch-shared__app.pri,v 1.3 2019/07/31 19:30:21 plunky Exp $

fix build for pkgsrc, by allowing qmake to link binaries in situ
and create an install target

--- shared_app.pri.orig	2019-02-27 15:06:55.000000000 +0000
+++ shared_app.pri
@@ -1,22 +1,21 @@
 include($$PWD/shared.pri)
 
 LIBS += \
-    -l$${RLIBNAME}ecmaapi \
-    -l$${RLIBNAME}gui \
-    -l$${RLIBNAME}entity \
-    -l$${RLIBNAME}operations \
-    -l$${RLIBNAME}spatialindex \
-    -lspatialindexnavel \
-    -l$${RLIBNAME}grid \
-    -l$${RLIBNAME}snap \
-    -l$${RLIBNAME}core \
-    -l$${RLIBNAME}stemmer \
-    -lstemmer
+    -L$$PWD/src/scripting/ecmaapi -l$${RLIBNAME}ecmaapi \
+    -L$$PWD/src/gui -l$${RLIBNAME}gui \
+    -L$$PWD/src/entity -l$${RLIBNAME}entity \
+    -L$$PWD/src/operations -l$${RLIBNAME}operations \
+    -L$$PWD/src/spatialindex -l$${RLIBNAME}spatialindex \
+    -L$$PWD/src/3rdparty/spatialindexnavel -lspatialindexnavel \
+    -L$$PWD/src/grid -l$${RLIBNAME}grid \
+    -L$$PWD/src/snap -l$${RLIBNAME}snap \
+    -L$$PWD/src/core -l$${RLIBNAME}core \
+    -L$$PWD/src/stemmer -l$${RLIBNAME}stemmer \
+    -L$$PWD/src/3rdparty/stemmer -lstemmer
 
 !r_no_opennurbs {
     LIBS += \
-        -lopennurbs \
-        -lzlib
+        -L$$PWD/src/3rdparty/opennurbs/opennurbs -lopennurbs
 }
 
 win32 {
