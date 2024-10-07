# Makefile for C Project

# Compiler
CC = gcc

# Compiler Flags
CFLAGS = -fdiagnostics-color=always -g -Wall -Wextra -Wconversion \
         -Wsign-conversion -Wshadow -Wpedantic -std=c17 \
         -D__USE_MINGW_ANSI_STDIO=1 -Iinclude

# Directories
SRC_DIR = src
INCLUDE_DIR = include
BUILD_DIR = build
BIN_DIR = bin

# Source and Header Files
SOURCES = $(wildcard $(SRC_DIR)/*.c)
OBJECTS = $(patsubst $(SRC_DIR)/%.c, $(BUILD_DIR)/%.o, $(SOURCES))

# Executable Name
TARGET = $(BIN_DIR)/clox.exe

# Default Target
all: $(TARGET)

# Link Object Files to Create Executable
$(TARGET): $(OBJECTS) | $(BIN_DIR)
	$(CC) $(CFLAGS) -o $@ $^

# Compile Source Files to Object Files
$(BUILD_DIR)/%.o: $(SRC_DIR)/%.c | $(BUILD_DIR)
	$(CC) $(CFLAGS) -c $< -o $@

# Create Build Directory
$(BUILD_DIR):
	mkdir $(BUILD_DIR)

# Create Bin Directory
$(BIN_DIR):
	mkdir $(BIN_DIR)

# Clean Build and Bin Directories
clean:
	del /Q $(BUILD_DIR)\*.o $(TARGET) 2>nul || rm -f $(BUILD_DIR)/*.o $(TARGET)

# Phony Targets
.PHONY: all clean
