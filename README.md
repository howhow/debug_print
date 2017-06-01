# debug_print
Linux:
x86_64
[![Code Health](https://landscape.io/github/howhow/debug_print/master/landscape.svg?style=flat)](https://landscape.io/github/howhow/debug_print/master)
[![Build Status](https://travis-ci.org/howhow/debug_print.svg?branch=master)](https://travis-ci.org/howhow/debug_print)
[![Coverage Status](https://coveralls.io/repos/github/howhow/debug_print/badge.svg?branch=master)](https://coveralls.io/github/howhow/debug_print?branch=master)

## Purpose
1. study how to impelmente debug print method
2. study makefile

## Feature
1. split print to stdout and stderr, easy to filter
2. colored print, easy to identify
3. leveled print, easy to control

## TODO
Split print to different target

## How to use
#### 1. Display Debug output
make DEBUG=YES && make test
#### 2. Perform code coverage
make DEBUG=YES && make test && make testcov
#### 3. Remove debug print
- just remove **DEBUG=YES** during make
- configure in code by function **DbgConfig(group, level)**
