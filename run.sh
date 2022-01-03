#!/usr/bin/env bash
set -e
make main
LD_LIBRARY_PATH=. ./main
