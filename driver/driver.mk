# Sub-folder makefile
#
#    @File:      driver.mk
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
MODULE = driver

# define expected lib
MOD_LIB = $(LIB_PREFIX)$(MODULE).$(LIB_POSTFIX)


# modify sys-make/config/build.config to control
CC_DEFS :=

# add srouce files, which would like to compile
SRC_FILES =
SRC_FILES += driver.c
SRC_FILES += local.c
SRC_FILES += uart.c
# modify sys-make/config/build.config to control

# add include search path
INC_PATH =
INC_PATH += $(TOP_DIR)/include
INC_PATH += $(TOP_DIR)/debug
INC_PATH += $(TOP_DIR)/$(MODULE)
INC_PATH += $(TOP_DIR)/$(MODULE)/local
INC_PATH += $(TOP_DIR)/$(MODULE)/uart

# add source file search path together with vpath
SRC_PATH =
SRC_PATH += $(TOP_DIR)/$(MODULE)
SRC_PATH += $(TOP_DIR)/$(MODULE)/local
SRC_PATH += $(TOP_DIR)/$(MODULE)/uart

vpath %.c $(SRC_PATH)

# use general compiler and compile rules
include $(MKFILE_DIR)/gcc.mk
include $(MKFILE_DIR)/rules.mk

