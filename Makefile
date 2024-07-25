# Makefile for building programs for x86 and ARM architectures
#
# Usage:
#   make         - Build all programs for both x86 and ARM
#   make x86     - Build all programs for x86 only
#   make arm     - Build all programs for ARM only
#   make clean   - Clean all build files
#
# Directories:
#   src/        - Source files directory
#   execs/x86/  - Directory for x86 executables
#   execs/arm/  - Directory for ARM executables

# Source and output directories
SRC_DIR := src
EXEC_DIR := execs
EXEC_X86_DIR := $(EXEC_DIR)/x86
EXEC_ARM_DIR := $(EXEC_DIR)/arm

# Compiler and flags
CC_X86 := gcc
CC_ARM := arm-linux-gnueabi-gcc
CFLAGS := -O2 -Wall
LDFLAGS :=

# Source files
SRC_FILES := $(wildcard $(SRC_DIR)/*.c)
SRC_NAMES := $(notdir $(SRC_FILES))
OBJ_FILES_X86 := $(SRC_NAMES:.c=.x86.o)
OBJ_FILES_ARM := $(SRC_NAMES:.c=.arm.o)

# Executables
EXEC_FILES_X86 := $(SRC_NAMES:.c=)
EXEC_FILES_ARM := $(SRC_NAMES:.c=ARM)

# Default target
all: x86 arm

# Build for x86
x86: $(EXEC_X86_DIR) $(EXEC_FILES_X86)

$(EXEC_X86_DIR):
	@mkdir -p $@

$(EXEC_FILES_X86): %: $(SRC_DIR)/%.c
	$(CC_X86) $(CFLAGS) -o $(EXEC_X86_DIR)/$@ $< $(LDFLAGS)

# Build for ARM
arm: $(EXEC_ARM_DIR) $(EXEC_FILES_ARM)

$(EXEC_ARM_DIR):
	@mkdir -p $@

$(EXEC_FILES_ARM): %ARM: $(SRC_DIR)/%.c
	$(CC_ARM) $(CFLAGS) -o $(EXEC_ARM_DIR)/$@ $< $(LDFLAGS)

# Clean build files
clean:
	@rm -rfv $(EXEC_X86_DIR) $(EXEC_ARM_DIR) $(OBJ_FILES_X86) $(OBJ_FILES_ARM)

.PHONY: all x86 arm clean

