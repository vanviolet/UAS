#!/usr/bin/env bash
set -euo pipefail

ROOT_DIR="$(cd "$(dirname "${BASH_SOURCE[0]}")" && pwd)"
BUILD_DIR="$ROOT_DIR/build"

mkdir -p "$BUILD_DIR"

g++ "$ROOT_DIR/main.cpp" \
    "$ROOT_DIR/PayrollApp.cpp" \
    "$ROOT_DIR/PayrollCalculator.cpp" \
    -std=c++17 -Wall -Wextra -O2 \
    -o "$BUILD_DIR/payroll"

echo "Binary available at $BUILD_DIR/payroll"
