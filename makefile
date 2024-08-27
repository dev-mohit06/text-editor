# Compiler
CC = gcc

# Directories
INCLUDE_DIR = include
SRC_DIR = src
BUILD_DIR = build

# Source files
SRC_FILES = $(SRC_DIR)/main.c $(SRC_DIR)/linked_list.c $(SRC_DIR)/file_operations.c

# Output binary
OUTPUT = $(BUILD_DIR)/main

# Compiler flags
CFLAGS = -I$(INCLUDE_DIR)

# Target to build the executable
all: $(OUTPUT) run

# Link object files to create the final executable
$(OUTPUT): $(SRC_FILES)
	$(CC) $(CFLAGS) $(SRC_FILES) -o $(OUTPUT)

# Run the executable after building
run: $(OUTPUT)
	@echo "Running the program..."
	@$(OUTPUT)

# Clean up build files
clean:
	rm -f $(OUTPUT)

# Phony targets to avoid conflicts with file names
.PHONY: all clean run