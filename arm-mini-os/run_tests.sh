#!/usr/bin/env bash

readonly TEST_EXECUTABLE=tests.out

set -e
set -x

gcc \
  test/calc_unittest.c \
  -I./source \
    source/utils.c \
    source/calc.c \
    source/die.c \
  -DTEST_NO_ARM \
  -o "${TEST_EXECUTABLE}"

./"${TEST_EXECUTABLE}"

rm "${TEST_EXECUTABLE}"
