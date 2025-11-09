#!/bin/bash

set -e

cd ~/develop/maze_c

rm -rf build

mkdir build

cd build

cmake ..
