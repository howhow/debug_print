# rules makefile
#
#    @File:     rules.mk
#    @Author:   How.Chen
#    @Version:  2.0
#    @Date:     9h/May/2017
#    @Note:
#               - V2.0
#               - add comments
#               - add debug print
#

# define general path and output for each sub module
OUTS = $(OUTPUT_DIR)/$(MODULE)
OBJS = $(addprefix $(OUTS)/,$(SRC_FILES:.c=.o))
DEPS = $(addprefix $(OUTS)/,$(SRC_FILES:.c=.d))
SRCS = $(addprefix $(TOP_DIR)/$(MODULE)/,$(SRC_FILES))

CC_DEFINE = $(addprefix -D, $(CC_DEFS))
CC_INC_PATH = $(addprefix -I , $(INC_PATH))

# workaround for link, need all objs at once
FULL_O=$(shell find $(OUTS) -name "*.o")

.PHONY: link clean check testcov

# generate lib file
$(OUTS)/$(MOD_LIB): $(OBJS)
	@ar cr $@ $^
	@echo "ar $(notdir $@)"

# compile from source to objs include for dependence
# $< means each %.c, $@ means each $(OUTS)/%.o
$(OUTS)/%.o: %.c
	@mkdir -p $(OUTS)
	@$(CC) $(CFLAG) $(CC_DEFINE) $(CC_INC_PATH) -MMD -c $< -o $@
	@echo "cc $(notdir $<)"

# workaround for link
# $(CFLAG) does not exported
link:
	@echo "Link executable: $(OUTPUT_DIR)/$(TARGET_NAME)"
	@gcc -ggdb -Wall -fprofile-arcs -ftest-coverage $(FULL_O) -Wl,-Map=$(OUTPUT_DIR)/$(TARGET_NAME).map -o $(OUTPUT_DIR)/$(TARGET_NAME)

check:
	@echo "mod: $(MODULE)"
	@echo "libs: $(MOD_LIB)"
	@echo "src_path: $(SRC_PATH)"
	@echo "inc_path: $(INC_PATH)"
	@echo "srcs: $(SRC_FILES)"
	@echo "outs: $(OUTS)"
	@echo "objs: $(OBJS)"
	@echo "dpes: $(DEPS)"
	@echo "flag: $(CFLAG)"
	@echo "targ: $@"
	@echo "enabled features: $(FEATURE)"
	@echo "cc defines: $(CC_DEFINE)"
	@echo "cc include: $(CC_INC_PATH)"

testcov:
	cd $(OUTS) && \
	for cfiles in $(SRCS); do \
		gcov -fb $$cfiles -o $(OUTS); \
	done
	cd $(TOP_DIR) 


# remove output for each sub module
clean:
	-@rm -r $(OUTS)

# include dependence if has
-include $(DEPS)

########## HISTORY ##########
# -V1.0
# - init commit
# - add rule for obj
# - add rule for depend
# - add rule for lib
#############################
