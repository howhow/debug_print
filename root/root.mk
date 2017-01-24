PROG = ../prog/DEMO

SRCS = $(wildcard *.c)
OBJS = $(patsubst %.c, %.o, $(SRCS))

$(PROG): $(SRCS)
	@mkdir -p ../prog
	@$(CC) $^ $(CFLAGS) -Wl,-Map=$(PROG).map $(LIBS) -o $@
	@echo "    Generate Program $(notdir $(PROG)) from $^"

.PHONY: clean
clean:
	@$(RM) -f $(OBJS) $(PROG)
	@$(RM) -f *.expand
	@$(RM) -rf ../prog ../libs
	@echo "    Remove Objects:   $(OBJS)"
	@echo "    Remove Libraries:  $(notdir $(PROG))"
