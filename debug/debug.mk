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

MODULE = debug

MOD_LIB = $(LIBS_DIR)/lib$(MODULE).a

SRCS = $(wildcard *.c)
OBJS = $(patsubst %.c, %.o, $(SRCS))
DEPS = $(patsubst %.c, %.d, $(SRCS))

$(MOD_LIB): $(OBJS)
	@mkdir -p $(LIBS_DIR)
	@$(AR) cr $@ $^
	@echo "    AR    $(notdir $@)"

%.o: %.c
	@$(CC) $(CFLAGS) $(INC_SRCH_PATH) -c $<
	@$(CC) $(CFLAGS) $(INC_SRCH_PATH) -MM $< > $*.d
	@echo "    CC    $<"


.PHONY: clean lint testcov
clean:
	@$(RM) -f $(MOD_LIB) $(OBJS) $(DEPS) *.gc*
	@echo "    Remove Obj:    $(OBJS)"
	@echo "    Remove Dep:    $(DEPS)"
	@echo "    Remove Lib:     $(notdir $(MOD_LIB))"


lint:
	$(LINT) $(INC_SRCH_PATH) $(SRCS)


testcov:
	for cfile in $(SRCS); do \
		gcov $$cfile; \
	done

-include $(DEPS)

