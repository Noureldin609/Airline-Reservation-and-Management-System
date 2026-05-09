# ===========================================
# Airline Reservation and Management System
# ===========================================

# Compiler settings
CXX := g++
CXXFLAGS := -std=c++17 -Wall -Iinclude

# Directory structure
SRC_DIR := src
OBJ_DIR := obj
BIN_DIR := bin
DB_DIR := database

# Output executable
TARGET := $(BIN_DIR)/AirlineSystem

# Source and object files
SRCS := $(wildcard $(SRC_DIR)/*.cpp)
OBJS := $(SRCS:$(SRC_DIR)/%.cpp=$(OBJ_DIR)/%.o)

# Default rule
all: $(TARGET)

# Build target
$(TARGET): $(OBJS)
	@mkdir -p $(BIN_DIR)
	$(CXX) $(CXXFLAGS) $(OBJS) -o $(TARGET)
	@echo " Build successful: $(TARGET)"

# Compile source files
$(OBJ_DIR)/%.o: $(SRC_DIR)/%.cpp
	@mkdir -p $(OBJ_DIR)
	$(CXX) $(CXXFLAGS) -c $< -o $@
	@echo " Compiled $< -> $@"

# Run the program (with database copy)
run: all
	@echo " Running Airline System..."
	@mkdir -p $(BIN_DIR)/$(DB_DIR)
	@cp -r $(DB_DIR)/* $(BIN_DIR)/$(DB_DIR)/
	@echo " Database copied to $(BIN_DIR)/$(DB_DIR)"
	@cd $(BIN_DIR) && ./AirlineSystem

# Clean compiled files
clean:
	@echo " Cleaning up..."
	rm -rf $(OBJ_DIR) $(BIN_DIR)
	@echo " Clean complete."

# Rebuild project
rebuild: clean all

.PHONY: all run clean rebuild
