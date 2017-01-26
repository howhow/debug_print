#!/bin/bash
set -x

make
make test
for x in ./**/*.c; do
    (cd "${x%/*}" && gcov "${x##/}")
done
