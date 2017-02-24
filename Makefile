CC        := gcc
LD        := gcc 
COLOR_ON 	:= color
COLOR_OFF	:=

PROGRAM = test_print

MAKE_DIR	= $(PWD)
MODULES		:= debug root
SRC_DIR		:= $(addprefix $(MAKE_DIR)/,$(MODULES))
BUILD_DIR	:= $(MAKE_DIR)/output

SRC			:= $(foreach sdir,$(SRC_DIR),$(wildcard $(sdir)/*.c))
OBJ			:= $(patsubst %.c,%.o,$(SRC))
DEP			:= $(patsubst %.c,%.d,$(SRC))

INCLUDES	:= $(addprefix -I,$(SRC_DIR))
INCLUDES	+= -I$(MAKE_DIR)/include

CFLAGS :=
CFLAGS += -Wall -O -ggdb -Wstrict-prototypes -Wno-pointer-sign -Werror 
CFLAGS += -D_DEBUG_ -D_REENTRANT
CFLAGS += -std=c99
TC_DEF :=

vpath %.c $(SRC_DIR)

define make-goal
$1/%.o: %.c
	@$(COLOR_OFF)$(CC) $(TC_DEF) $(CFLAGS) $(INCLUDES) -c $$< -o $$@
	@echo "CC    $$*.c"
endef

.PHONY: all checkdirs clean help flowchart
all: checkdirs $(BUILD_DIR)/$(PROGRAM)
	
$(BUILD_DIR)/$(PROGRAM): $(OBJ)
	@$(LD) $^ -o $@
	@echo "LD    $(PROGRAM)"
	

checkdirs: $(BUILD_DIR)

$(BUILD_DIR):
	mkdir -p $@

clean: 
	rm -f $(OBJ) $(DEP) $(BUILD_DIR)/$(PROGRAM)
	rm -rf $(BUILD_DIR)

help:
	@echo "SRC DIR:    $(SRC_DIR:$(MAKE_DIR)/%=%)"
	@echo "Build DIR:  $(BUILD_DIR:$(MAKE_DIR)/%=%)"
	@echo "Source:     $(SRC:$(MAKE_DIR)/%=%)"
	@echo "Obj:        $(OBJ:$(MAKE_DIR)/%=%)"
	@echo "Dep:        $(DEP:$(MAKE_DIR)/%=%)"
	@echo "Includes:   $(INCLUDES)"

flowchart:
	@cflow2dot pdf ${SRC}

$(foreach sdir,$(SRC_DIR),$(eval $(call make-goal,$(sdir))))

