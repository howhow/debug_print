#!/bin/bash

WORK=`pwd`
echo "Searching Files"
find $WORK						\
	-path "$WORK/mw" -prune -o	\
	-type f -name "*.[c|h]" > cscope.files

echo "Generate cscope dependent"
#cscope -b -k -i cscope.files
cscope -bkq

echo "Generate ctags dependent"
ctags --sort=foldcase -L cscope.files

echo "ALL tags generation done!!"
