#!/usr/bin/env bash

set -e

readonly BINARY_NAME=calc

readonly SOURCE_FILES=(
  functions.s
  calc.c
)

: ${CC:=arm-linux-gnueabihf-gcc}
readonly C_OPTS=(
  -O3
)


set -x

"${CC}" \
  "${C_OPTS[@]}" \
  "${SOURCE_FILES[@]}" \
  -o "${BINARY_NAME}"
  
"./${BINARY_NAME}"
