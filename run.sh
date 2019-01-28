#!/usr/bin/env bash

set -e

: ${CC:=arm-linux-gnueabihf-gcc}
readonly BINARY_NAME=calc
readonly SOURCE_FILES=(\
  functions.s \
  calc.c \
)
readonly C_OPTS=(
  -O3 \
)

set -x

"${CC}" \
  "${C_OPTS[@]}" \
  "${SOURCE_FILES[@]}" \
  -o "${BINARY_NAME}"
  
"./${BINARY_NAME}"
