# General Makefile
#
#    @File:      Makefile
#    @Author:    How.Chen
#    @Version:   2.0
#    @Date:      25th/Jan/2017
#                - V1.0
#                - init commit

MAKE_DIR = $(PWD)

ROOT_DIR	:= $(MAKE_DIR)/root 
DRIVER_DIR	:= $(MAKE_DIR)/driver
INCLUDE_DIR	:= $(MAKE_DIR)/include
DEBUG_DIR	:= $(MAKE_DIR)/debug
OUTPUT_DIR	:= $(MAKE_DIR)/output
LIBS_DIR	:= $(OUTPUT_DIR)/libs
OBJS_DIR	:= $(OUTPUT_DIR)/objs
DEPS_DIR	:= $(OUTPUT_DIR)/deps

INC_SRCH_PATH := 
INC_SRCH_PATH += -I$(ROOT_DIR)
INC_SRCH_PATH += -I$(DRIVER_DIR) 
INC_SRCH_PATH += -I$(INCLUDE_DIR)
INC_SRCH_PATH += -I$(DEBUG_DIR)

LIB_SRCH_PATH :=
LIB_SRCH_PATH += -L$(LIBS_DIR)


COLOR_ON = color
COLOR_OFF = 
CC = $(COLOR_ON)gcc
#CC = $(COLOR_OFF)gcc
LD = ld

LINT = splint

CLIBS :=
CLIBS += -ldebug

CFLAGS :=
CFLAGS += $(INC_SRCH_PATH) $(LIB_SRCH_PATH) 
CFLAGS += -Wall -O -ggdb -Wstrict-prototypes -Wno-pointer-sign
CFLAGS += -D_DEBUG_ -D_REENTRANT

LDFLAGS :=

export MAKE_DIR CC LD CFLAGS LDFLAGS CLIBS LINT INC_SRCH_PATH 
export OUTPUT_DIR LIBS_DIR OBJS_DIR DEPS_DIR

all:
	@$(MAKE) -C debug -f debug.mk
	@$(MAKE) -C root -f root.mk

.PHONY: clean
clean:
	@$(MAKE) -C debug -f debug.mk clean
	@$(MAKE) -C root -f root.mk clean

.PHONY: help
help:
	@$(MAKE) -C debug -f debug.mk help
	@$(MAKE) -C root -f root.mk help

.PHONY: lint
lint:
	$(MAKE) -C debug -f debug.mk lint 
