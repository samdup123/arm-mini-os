#!/usr/bin/env bash

set -e

: ${CC:=gcc}
: ${OBJCOPY:=objcopy}

readonly BINARY_NAME=kernel.img

readonly SOURCES=(
  source/*.c
  source/*.s
)

readonly COPTS=(
  -O3
)

set -x

"${CC}" \
  "${COPTS[@]}" \
  "${SOURCES[@]}" \
  -o "${BINARY_NAME}"

"${OBJCOPY}" -O binary "${BINARY_NAME}"

