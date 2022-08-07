#!/usr/bin/env bash
set -eu

mkdir -p build
cd build
cmake ..
make
cd -

