#!/usr/bin/env bash
set -eu

mkdir -p build
cd build
cmake ..
make -j2
cd -

