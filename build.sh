#!/usr/bin/env bash

set -e

: ${CC:=gcc}
: ${OBJCOPY:=objcopy}

readonly ELF_NAME=kernel.elf
readonly IMAGE_NAME=kernel.img

readonly SOURCES=(
  source/*.c
  source/*.s
)

readonly COPTS=(
  -O3
  -std=c11
  -march=armv6
  -mtune=arm1176jzf-s
  -mfloat-abi=hard
  -ffast-math
  -Wl,--no-undefined,-Tkernel.ld,-N
  -Wa,-mfpu=vfpv2
)

set -x

"${CC}" \
  "${COPTS[@]}" \
  "${SOURCES[@]}" \
  -o "${ELF_NAME}"

"${OBJCOPY}" "${ELF_NAME}" -O binary > kernel.list

