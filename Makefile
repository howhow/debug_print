# General Makefile
#
# 	@Author:	How.Chen
#	@Version:	2.0
#	@Date:		28th/Aug/2012

MAKE_DIR = $(PWD)

ROOT_DIR	:= $(MAKE_DIR)/root 
DRV_DIR		:= $(MAKE_DIR)/driver
INCLUDE_DIR := $(MAKE_DIR)/include
DEBUG_DIR	:= $(MAKE_DIR)/debug

INC_SRCH_PATH := 
INC_SRCH_PATH += -I$(ROOT_DIR)
INC_SRCH_PATH += -I$(DRV_DIR) 
INC_SRCH_PATH += -I$(INCLUDE_DIR)
INC_SRCH_PATH += -I$(DEBUG_DIR)

LIB_SRCH_PATH :=
LIB_SRCH_PATH += -L$(MAKE_DIR)/libs


COLOR_ON = color
COLOR_OFF = 
CC = $(COLOR_ON)gcc
#CC = $(COLOR_OFF)gcc
LD = ld

LINT = splint

LIBS :=
LIBS += -ldebug
#LIBS += -ldriver -lmw -lm -lpthread

CFLAGS :=
CFLAGS += $(INC_SRCH_PATH) $(LIB_SRCH_PATH) 
CFLAGS += -Wall -O -ggdb -Wstrict-prototypes -Wno-pointer-sign
CFLAGS += -D_DEBUG_ -D_REENTRANT

LDFLAGS :=

export MAKE_DIR CC LD CFLAGS LDFLAGS LIBS LINT INC_SRCH_PATH

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

.PHONY: lint
lint:
	$(MAKE) -C debug -f debug.mk lint 
