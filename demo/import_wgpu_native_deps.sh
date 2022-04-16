#!/usr/bin/env bash
set -e
if [ "$1" = "" ] ; then
	echo "Usage: $0 <path/to/wgpu-native>"
	echo
	echo "This script assumes the the path is a git clone:"
	echo "  $ git clone https://github.com/gfx-rs/wgpu-native"
	echo "It builds wgpu-native and imports the required dependencies:"
	echo "  libwgpu_native.so"
	echo "  webgpu.h"
	echo
	echo "Alternatively, you can unpack a release from here:"
	echo "  https://github.com/gfx-rs/wgpu-native/releases"
	echo
	exit 1
fi
to=$(pwd)
cd $1
if ! grep -qF 'name = "wgpu-native"' Cargo.toml ; then
	echo "'$1' does not appear to be a wgpu-native root directory"
	exit 1
fi

git submodule init
git submodule update
cargo build

cp target/debug/libwgpu_native.so $to/
cp ffi/webgpu-headers/webgpu.h $to/

