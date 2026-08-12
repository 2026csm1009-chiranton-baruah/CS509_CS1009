# =========================
# CS509 Assignment 02
# Makefile
# =========================

CXX      := g++
CXXFLAGS := -std=c++17 -O2 -Wall -Wextra -Iinclude

BIN_DIR  := bin
DRIVER   := driver/driver.cpp
TARGET   := $(BIN_DIR)/driver

# Default target
all: $(TARGET)

# Create bin directory if needed
$(BIN_DIR):
	mkdir -p $(BIN_DIR)

# Build the assignment driver
$(TARGET): $(DRIVER) | $(BIN_DIR)
	$(CXX) $(CXXFLAGS) $(DRIVER) -o $(TARGET)

# Run the assignment driver
run: $(TARGET)
	./$(TARGET)

# Remove build artifacts
clean:
	rm -rf $(BIN_DIR)

# Rebuild from scratch
rebuild: clean all

.PHONY: all run clean rebuild
