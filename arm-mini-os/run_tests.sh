#!/usr/bin/env bash

set -e
set -x

gcc test/calc_unittest.c -I./source source/calc.c source/utils.c
./a.out
rm a.out

