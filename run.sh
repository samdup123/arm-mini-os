#!/usr/bin/env bash

set -ex

gcc -O3 functions.s calc.c -o calc && ./calc

