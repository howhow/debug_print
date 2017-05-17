# compiler makefile
#
#    @File:      gcc.mk
#    @Author:    How.Chen
#    @Version:   1.0
#    @Date:      27h/April/2017
#    @Note:
#                -V1.0
#                - init commit
#

# define compiler
CC :=
CC += gcc

#define compiler flag
# TODO:: detect debug and release build
CFLAG :=
ifeq '$(DEBUG)' 'YES'
	CFLAG += -ggdb -Wall -D_DEBUG_
endif

CFLAG += -fprofile-arcs -ftest-coverage
CFLAG += -D_REENTRANT
CFLAG += -Wstrict-prototypes -Wno-pointer-sign -Werror

