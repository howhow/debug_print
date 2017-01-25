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
	@$(RM) -f $(DEPS) $(OBJS) $(PROG)
	@$(RM) -rf $(OUTPUT_DIR) $(LIBS_DIR)
	@echo "    Remove Objects:   $(OBJS)"
	@echo "    Remove Program:    $(notdir $(PROG))"

-include $(DEPS)
