# define useful directory path
TOP_DIR = $(PWD)
MKFILE_DIR = $(TOP_DIR)/sys-make
CFG_DIR = $(MKFILE_DIR)/config
OUTPUT_DIR = $(TOP_DIR)/output

# define useful prefix/postfix
LIB_PREFIX = lib
LIB_POSTFIX = a

# executable name
TARGET_NAME = debug_print

# include build configuration
# FEATURE define in it
include $(CFG_DIR)/build.config

# export var, which need be known by sub-makefile
export TOP_DIR MKFILE_DIR OUTPUT_DIR
export LIB_PREFIX LIB_POSTFIX
export TARGET_NAME

all: obj link

obj:
	@$(MAKE) -f $(TOP_DIR)/debug/debug.mk
	@$(MAKE) -f $(TOP_DIR)/driver/driver.mk
	@$(MAKE) -f $(TOP_DIR)/root/root.mk

# link workaround
# pass link to rules.mk to trigger link
link:
	@$(MAKE) -f $(MKFILE_DIR)/rules.mk link

# check
# to display each module build info
check:
	@$(MAKE) -f $(TOP_DIR)/debug/debug.mk check
	@$(MAKE) -f $(TOP_DIR)/driver/driver.mk check
	@$(MAKE) -f $(TOP_DIR)/root/root.mk check

# remove ouyput
clean:
	@$(MAKE) -f $(TOP_DIR)/debug/debug.mk clean
	@$(MAKE) -f $(TOP_DIR)/driver/driver.mk clean
	@$(MAKE) -f $(TOP_DIR)/root/root.mk clean
	-rm -r $(OUTPUT_DIR)

flowchart:
	@cflow2dot pdf ${SRC}

test:
	$(OUTPUT_DIR)/$(TARGET_NAME)

testcov:
	@$(MAKE) -f $(TOP_DIR)/debug/debug.mk testcov
	@$(MAKE) -f $(TOP_DIR)/driver/driver.mk testcov
	@$(MAKE) -f $(TOP_DIR)/root/root.mk testcov

testcovr:
	gcovr -r $(TOP_DIR)
	gcovr -r $(TOP_DIR) -b
