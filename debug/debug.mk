# Sub-folder makefile
#
# 	@Author:	How.Chen
#	@Version:	2.0
#	@Date:		28th/Aug/2012
#	@Note:		At V2.0, add generate library
#				remove system print and customized

LIB = $(MAKE_DIR)/libs/libdebug.a
SRCS = $(wildcard *.c)
OBJS = $(patsubst %.c, %.o, $(SRCS))
DEPS = $(patsubst %.c, %.d, $(SRCS))

$(LIB): $(OBJS)
	@mkdir -p ../libs
#	@$(AR) crv $@ $^
	@$(AR) cr $@ $^
	@echo "    Archive    $(notdir $@)"

$(OBJS): $(SRCS)
	@$(CC) $(CFLAGS) $(INC_SRCH_PATH) -c $^
#	@$(CC) $(CFLAGS) $(INC_SRCH_PATH) -MM $(SRC) > $(DEPS)
	@echo "    CC        $(OBJS)"

.PHONY: clean
clean:
	@$(RM) -f $(LIB) $(OBJS) $(DEPS)
	@$(RM) -f *.expand
	@echo "    Remove Objects:   $(OBJS)"
	@echo "    Remove depends:   $(DEPS)"
	@echo "    Remove Libraries:  $(notdir $(LIB))"

.PHONY: lint 
lint:
	$(LINT) $(INC_SRCH_PATH) $(SRCS)
