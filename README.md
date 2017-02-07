# debug_print
Linux:
x86_64 [![Build Status](https://travis-ci.org/howhow/debug_print.svg?branch=master)](https://travis-ci.org/howhow/debug_print)

## Purpose
1. study how to impelmente debug print method
2. study makefile

## Feature
1. split print to stdout and stderr
2. colored print
3. leveled print

## Known issue
1. Makefile dependence problem, modify sub component c file, will not trigger a new link
2. print level will impact all module, need split it into individual
