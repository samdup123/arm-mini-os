#!/usr/bin/env bash

set -e
set -x

gcc source/calc_unittest.c source/calc.c source/utils.c
./a.out
rm a.out

