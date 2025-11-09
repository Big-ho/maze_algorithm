#!/bin/bash

set -e

echo "=== CMake Configure ==="
cmake -S . -B build

echo "=== Build ==="
cmake --build build

echo "=== Build Complete! ==="
