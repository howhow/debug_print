# debug_print
Linux:
x86_64
[![Code Health](https://landscape.io/github/howhow/debug_print/master/landscape.svg?style=flat)](https://landscape.io/github/howhow/debug_print/master)
[![Build Status](https://travis-ci.org/howhow/debug_print.svg?branch=master)](https://travis-ci.org/howhow/debug_print)
[![Coverage Status](https://coveralls.io/repos/github/howhow/debug_print/badge.svg?branch=master)](https://coveralls.io/github/howhow/debug_print?branch=master)

## Purpose
1. study how to impelmente debug print method under Linux
2. study makefile
3. study coding with vim/cscope/YCM

## Feature
1. split print to different module, easy to filter
2. colored print, easy to identify
3. leveled print, easy to control

## TODO
1. Automatically detect OS arch in Makefile
2. Delivery debug print function as a LIB
3. Demo link list

## How to use
#### 1. Display Debug output
- make DEBUG=YES && make test, or
- ./post_test.sh DEBUG=YES
#### 2. Perform code coverage
make DEBUG=YES && make test && make testcov
#### 3. Remove debug print
- just remove **DEBUG=YES** during make, or
- configure in code by function **DbgConfig(group, level)**
