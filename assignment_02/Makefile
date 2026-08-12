# ==================================================
# CS509 - Assignment 02
# Builds only the submission code (not tools/)
# ==================================================

CXX := g++
CXXFLAGS := -std=c++17 -O2 -Wall -Wextra -Iinclude

BIN_DIR := bin
TARGET := $(BIN_DIR)/assignment_02_driver

DRIVER := driver/assignment_02_driver.cpp

# Default target
all: $(TARGET)

# Create bin directory if needed
$(BIN_DIR):
	mkdir -p $(BIN_DIR)

# Build the assignment driver
$(TARGET): $(DRIVER) | $(BIN_DIR)
	$(CXX) $(CXXFLAGS) $(DRIVER) -o $(TARGET)

# Run the assignment
run: $(TARGET)
	./$(TARGET)

# Remove build artifacts
clean:
	rm -rf $(BIN_DIR)

# Full rebuild
rebuild: clean all

.PHONY: all run clean rebuild
