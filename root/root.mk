# Sub-folder makefile
#
#    @File:      root.mk
#    @Author:    How.Chen
#    @Version:   2.0
#    @Date:      16h/May/2017
#    @Note:
#                -V1.0
#                - init commit
#                - add generate library
#                - remove system print and customized
#
#                V2.0
#                - add dependence check

# define module name for compile use
MODULE = root

# define expected lib
MOD_LIB = $(LIB_PREFIX)$(MODULE).$(LIB_POSTFIX)


CC_DEFS :=
# modify sys-make/config/build.config to control

# add srouce files, which would like to compile
SRC_FILES =
SRC_FILES += main.c

# add include search path
INC_PATH =
INC_PATH += $(TOP_DIR)/include
INC_PATH += $(TOP_DIR)/debug
INC_PATH += $(TOP_DIR)/driver

# add source file search path together with vpath
SRC_PATH =
SRC_PATH += $(TOP_DIR)/$(MODULE)

vpath %.c $(SRC_PATH)

# use general compiler and compile rules
include $(MKFILE_DIR)/gcc.mk
include $(MKFILE_DIR)/rules.mk

