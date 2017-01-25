# Sub-folder makefile
#
# 	@Author:	How.Chen
#	@Version:	2.0
#	@Date:		25th/Jan/2017
#	@Note:		
#				-V1.0
#				- init commit
#				- add generate library
#				- remove system print and customized
#
#				V2.0
#				- add dependence check

MODULE = debug

MOD_LIB = $(LIBS_DIR)/lib$(MODULE).a

SRCS = $(wildcard *.c)
OBJS = $(patsubst %.c, %.o, $(SRCS))
DEPS = $(patsubst %.c, %.d, $(SRCS))

$(MOD_LIB): $(OBJS)
	@mkdir -p $(LIBS_DIR)
#	@$(AR) crv $@ $^
	@$(AR) cr $@ $^
	@echo "    AR    $(notdir $@)"

%.o: %.c
	@$(CC) $(CFLAGS) $(INC_SRCH_PATH) -c $<
	@$(CC) $(CFLAGS) $(INC_SRCH_PATH) -MM $< > $*.d
	@echo "    CC    $<"


.PHONY: clean
clean:
	@$(RM) -f $(MOD_LIB) $(OBJS) $(DEPS)
	@$(RM) -f *.expand
	@echo "    Remove Objects:   $(OBJS)"
	@echo "    Remove depends:   $(DEPS)"
	@echo "    Remove Libraries:  $(notdir $(MOD_LIB))"


.PHONY: lint
lint:
	$(LINT) $(INC_SRCH_PATH) $(SRCS)

-include $(DEPS)
