# Sub-folder makefile
#
#    @File:      debug.mk
#    @Author:    How.Chen
#    @Version:   2.0
#    @Date:      26h/Jan/2017
#    @Note:
#                -V1.0
#                - init commit
#                - add generate library
#                - remove system print and customized
#
#                V2.0
#                - add dependence check

# define module name for compile use
MODULE = debug

# define expected lib
MOD_LIB = $(LIB_PREFIX)$(MODULE).$(LIB_POSTFIX)


CC_DEFS :=
ifeq '$(filter FEATURE_1, $(FEATURE))' 'FEATURE_1'
	CC_DEFS += C_DEF_1
endif

# add srouce files, which would like to compile
SRC_FILES =
SRC_FILES += debug.c
# modify sys-make/config/build.config to control
ifeq '$(filter INSTRUMENT, $(FEATURE))' 'INSTRUMENT'
	SRC_FILES += instrument.c
	SRC_FILES += uart_print.c
endif

# add include search path
INC_PATH =
INC_PATH += $(TOP_DIR)/include
INC_PATH += $(TOP_DIR)/$(MODULE)
INC_PATH += $(TOP_DIR)/driver


# add source file search path together with vpath
SRC_PATH =
SRC_PATH += $(TOP_DIR)/$(MODULE)

vpath %.c $(SRC_PATH)
vpath %.h $(INC_PATH)

# use general compiler and compile rules
include $(MKFILE_DIR)/gcc.mk
include $(MKFILE_DIR)/rules.mk

