CC := gcc
CFLAGS := -Wall -Wextra -O2

SHELL_BIN := crsh
MAIN_SRC := main.c
EXAMPLES_DIR := examples
BIN_DIR := bin

EXAMPLES_SRC := $(wildcard $(EXAMPLES_DIR)/*.c)
EXAMPLES_BINS := $(patsubst $(EXAMPLES_DIR)/%.c, $(BIN_DIR)/%, $(EXAMPLES_SRC))

all: $(SHELL_BIN) $(EXAMPLES_BINS)

$(SHELL_BIN): $(MAIN_SRC)
	$(CC) $(CFLAGS) -o $@ $^

$(BIN_DIR)/%: $(EXAMPLES_DIR)/%.c | $(BIN_DIR)
	$(CC) $(CFLAGS) -o $@ $<

$(BIN_DIR):
	mkdir -p $(BIN_DIR)

clean:
	rm -f $(SHELL_BIN) $(BIN_DIR)/*

.PHONY: all clean
