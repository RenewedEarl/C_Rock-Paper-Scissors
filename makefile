# Project Config

TARGET = main

CC = gcc

SRC_DIR = src
INC_DIR = include
BUILD_DIR = build

# Compiler Flags

CSTD = -std=c11

WARNINGS = -Wall -Wextra -Wpedantic

DEBUG_FLAGS = -g -O0
RELEASE_FLAGS = -O2

CFLAGS = $(CSTD) $(WARNINGS) $(DEBUG_FLAGS) -I$(INC_DIR)

# Source Files

SRCS = main.c $(wildcard $(SRC_DIR)/*.c)

OBJS = $(patsubst %.c,$(BUILD_DIR)/%.o,$(notdir $(SRCS)))

DEPS = $(OBJS:.o=.d)

# Default Target

all: $(TARGET)

# Build Executable

$(TARGET): $(OBJS)
	$(CC) $(OBJS) -o $(TARGET)

# Compile main.c file

$(BUILD_DIR)/%.o: %.c
	@mkdir -p $(BUILD_DIR)
	$(CC) $(CFLAGS) -MMD -MP -c $< -o $@

# Compile Object Files

$(BUILD_DIR)/%.o: $(SRC_DIR)/%.c
	@mkdir -p $(BUILD_DIR)
	$(CC) $(CFLAGS) -MMD -MP -c $< -o $@

# Run Program

run: all
	./$(TARGET)

# Release Build

release: CFLAGS = $(CSTD) $(WARNINGS) $(RELEASE_FLAGS) -I$(INC_DIR)
release: clean all

# Clean Build Files

clean:
	rm -rf $(BUILD_DIR) $(TARGET)

# Rebuild

rebuild: clean all

# Include Dependencies

-include $(DEPS)

# Phony Targets

.PHONY: all run clean rebuild release
