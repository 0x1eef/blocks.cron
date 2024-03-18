##
# Compiler and compiler flags
CC = cc
CFLAGS = -Wall -Wextra -pedantic -L/usr/local/lib/ -I/usr/local/include/ -lfetch

##
# Directories
BUILD_DIR = ${.CURDIR}/build
SRC_DIR = src
INC_DIR = include
BIN_DIR = $(BUILD_DIR)/bin
VENDOR_DIR = vendor

##
# Files
SRC_FILES = $(SRC_DIR)/*.c $(SRC_DIR)/**/*.c $(VENDOR_DIR)/*/src/*.c
BIN_FILE = $(BIN_DIR)/blocklist

##
# Targets
build: clean $(BIN_FILE)

install:
	@if [ -e "$(BIN_FILE)" ]; then \
		if [ "$$(uname)" = "OpenBSD" ]; then \
			flags="-s"; \
		else \
			flags="-s -v"; \
		fi; \
		install $${flags} $(BIN_FILE) /usr/local/bin/blocklist; \
	fi

clean:
	rm -rf $(BIN_DIR)

$(BIN_FILE):
	mkdir -p $(BIN_DIR)
	$(CC) -I$(INC_DIR) -Ivendor/isinetaddr/include $(CFLAGS) $(SRC_FILES) -o $@ $^

format:
	clang-format -style=file:.clang-format -i src/*.c src/command/*.c

.PHONY: build install clean styleguide
