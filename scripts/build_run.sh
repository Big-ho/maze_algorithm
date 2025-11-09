#!/bin/bash

set -e

EXECUTABLE_NAME="maze_c"
BUILD_DIR="build"

echo "=== CMake Configure ==="
cmake -S . -B "${BUILD_DIR}"

echo "=== Build ==="
cmake --build "${BUILD_DIR}"

EXECUTABLE_PATH="./${BUILD_DIR}/${EXECUTABLE_NAME}"

if [ -x "${EXECUTABLE_PATH}" ]; then
    echo "=== Build Complete! ==="
    echo "=== Running ${EXECUTABLE_NAME} ==="

    "${EXECUTABLE_PATH}"
else
    echo "Error: Executable file not found at ${EXECUTABLE_PATH}"
    exit 1
fi