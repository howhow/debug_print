#!/bin/bash

#locate current work dir
#better to put this file at top source code
TOP_DIR=$(pwd)

#start to find relevant file
echo "find ALL c and h files"
find "$TOP_DIR" -type f -name "*.[c|h]" > cscope.files

echo "find ALL asm files"
find "$TOP_DIR" -type f -name "*.asm" >> cscope.files

echo "find ALL make related files"
find "$TOP_DIR" -type f -name "*.mk" >> cscope.files
find "$TOP_DIR" -type f -name "makefile" >> cscope.files
find "$TOP_DIR" -type f -name "Makefile" >> cscope.files

echo "find ALL config related files"
find "$TOP_DIR" -type f -name "*.config" >> cscope.files

#build tag and cscope file
echo "build tags"
cscope -bkq -i cscope.files
#cscope -bkq
#ctags --sort=foldcase -L cscope.files
ctags -L cscope.files
echo "ALL done!!!"

