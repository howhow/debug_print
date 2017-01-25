# General Makefile
#
# 	@Author:	How.Chen
#	@Version:	2.0
#	@Date:		28th/Aug/2012

MAKE_DIR = $(PWD)

ROOT_DIR	:= $(MAKE_DIR)/root 
DRIVER_DIR	:= $(MAKE_DIR)/driver
INCLUDE_DIR := $(MAKE_DIR)/include
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
#LIBS += -ldriver -lmw -lm -lpthread

CFLAGS :=
CFLAGS += $(INC_SRCH_PATH) $(LIB_SRCH_PATH) 
CFLAGS += -Wall -O -ggdb -Wstrict-prototypes -Wno-pointer-sign
CFLAGS += -D_DEBUG_ -D_REENTRANT

LDFLAGS :=

export MAKE_DIR CC LD CFLAGS LDFLAGS CLIBS LINT INC_SRCH_PATH 
export OUTPUT_DIR LIBS_DIR OBJS_DIR DEPS_DIR

all:
	@$(MAKE) -C debug -f debug.mk
#	@$(MAKE) -C driver -f driver.mk
#	@$(MAKE) -C mw -f mw.mk
	@$(MAKE) -C root -f root.mk
#	@$(MAKE_DIR)/test.sh

.PHONY: clean
clean:
	@$(MAKE) -C debug -f debug.mk clean
#	@$(MAKE) -C driver -f driver.mk clean
#	@$(MAKE) -C mw -f mw.mk clean
	@$(MAKE) -C root -f root.mk clean

.PHONY: help
help:
	@$(MAKE) -C debug -f debug.mk help
	@$(MAKE) -C root -f root.mk help

.PHONY: lint
lint:
	$(MAKE) -C debug -f debug.mk lint 
