# Sub-folder makefile
#
#    @File:      root.mk
#    @Author:    How.Chen
#    @Version:   2.0
#    @Date:      26h/Jan/2017
#    @Note:
#                -V1.0
#                - init commit
#                - remove system print and customized
#
#                V2.0
#                - add dependence check

PROG = $(OUTPUT_DIR)/test_print

SRCS = $(wildcard *.c)
OBJS = $(patsubst %.c, %.o, $(SRCS))
DEPS = $(patsubst %.c, %.d, $(SRCS))

$(PROG): $(OBJS)
	@mkdir -p $(OUTPUT_DIR) 
	@$(CC) $^ $(CFLAGS) -Wl,-Map=$(PROG).map $(CLIBS) -o $@
	@echo "    LD    $(notdir $(PROG))"

%.o: %.c
	@$(CC) $(CFLAGS) $(INC_SRCH_PATH) -c $<
	@$(CC) $(CFLAGS) $(INC_SRCH_PATH) -MM $< > $*.d
	@echo "    CC    $<"


.PHONY: clean
clean:
	@$(RM) -f $(DEPS) $(OBJS) $(PROG) *.gc*
	@$(RM) -rf $(OUTPUT_DIR) $(LIBS_DIR)
	@echo "    Remove Obj:    $(OBJS)"
	@echo "    Remove Dep:    $(DEPS)"
	@echo "    Remove Prog:    $(notdir $(PROG))"

.PHONY: test
test:
	$(PROG)

.PHONY: testcov
testcov: $(SRCS)
	gcov $(SRCS)

-include $(DEPS)

