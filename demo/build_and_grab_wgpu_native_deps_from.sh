#!/usr/bin/env bash
set -e
if [ "$1" = "" ] ; then
	echo "Usage: $0 <path/to/wgpu-native/root>"
	exit 1
fi
to=$(pwd)
cd $1
if ! grep -qF 'name = "wgpu-native"' Cargo.toml ; then
	echo "does not appear to be a wgpu-native root directory"
	exit 1
fi

git submodule init
git submodule update
cargo build

cp target/debug/libwgpu_native.so $to/
cp ffi/webgpu-headers/webgpu.h $to/
cp ffi/wgpu.h $to/
cd $to

# patch wgpu.h
patch -p1 << HERE
--- a/wgpu.h
+++ b/wgpu.h
@@ -1,7 +1,7 @@
 #ifndef WGPU_H_
 #define WGPU_H_
 
-#include "webgpu-headers/webgpu.h"
+#include "webgpu.h"
 
 typedef enum WGPUNativeSType {
     // Start at 6 to prevent collisions with webgpu STypes
HERE

