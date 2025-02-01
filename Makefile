# Compiler and flags
CC := clang
CFLAGS := -Wall -Wextra -O2

# Files and directories
SHELL_BIN := shell
MAIN_SRC := main.c
EXAMPLES_DIR := examples
EXAMPLES_SRC := $(wildcard $(EXAMPLES_DIR)/*.c)
EXAMPLES_BINS := $(patsubst $(EXAMPLES_DIR)/%.c, a.%, $(EXAMPLES_SRC))

# Default target builds both the shell and all examples
all: $(SHELL_BIN) $(EXAMPLES_BINS)

# Build the main shell binary from main.c
$(SHELL_BIN): $(MAIN_SRC)
	$(CC) $(CFLAGS) -o $@ $^

# Build each example binary from its corresponding .c file in examples/
a.%: $(EXAMPLES_DIR)/%.c
	$(CC) $(CFLAGS) -o $@ $<

# Clean up generated binaries
clean:
	rm -f $(SHELL_BIN) a.*

.PHONY: all clean
