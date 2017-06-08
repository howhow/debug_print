#!/bin/bash
set -x

make $1 && make test && make testcov && make testcovr && make clean

