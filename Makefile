##
# Compiler and compiler flags
CC = cc
CFLAGS = -Wall -Wextra -pedantic -L/usr/local/lib/ -I/usr/local/include/ -lfetch

##
# Directories
SRC_DIR = src
INC_DIR = include
BIN_DIR = bin
VENDOR_DIR = vendor

##
# Files
SRC_FILES = $(SRC_DIR)/*.c $(SRC_DIR)/**/*.c $(VENDOR_DIR)/*/src/*.c
BIN_FILE = $(BIN_DIR)/blocklist

##
# Targets
build: $(BIN_FILE)

clean:
	rm -rf $(BIN_DIR)

$(BIN_FILE):
	mkdir -p $(BIN_DIR)
	$(CC) -I$(INC_DIR) -Ivendor/isinetaddr/include $(CFLAGS) $(SRC_FILES) -o $@ $^

linter:
	uncrustify -c .styleguide.cfg --no-backup src/*.c

.PHONY: build clean
