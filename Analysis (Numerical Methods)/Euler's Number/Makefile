# Compiler
CXX = g++

# Compiler flags
CXXFLAGS = -std=c++11 -Wall

# Source files
SRC_FILES = euler.cpp main.cpp

# Object files directory
OBJ_DIR = objects

# Object files (inside the OBJ_DIR)
OBJ_FILES = $(SRC_FILES:%.cpp=$(OBJ_DIR)/%.o)

TARGET = euler_program

# Default target
all: $(TARGET)

# Linking the executable
$(TARGET): $(OBJ_FILES)
	$(CXX) $(CXXFLAGS) -o $(TARGET) $(OBJ_FILES)

# Compiling source files into objects
$(OBJ_DIR)/%.o: %.cpp | $(OBJ_DIR)
	$(CXX) $(CXXFLAGS) -c $< -o $@

$(OBJ_DIR):
	mkdir -p $(OBJ_DIR)

# Clean up
clean:
	rm -f $(TARGET) $(OBJ_FILES)
	rmdir $(OBJ_DIR) 2>/dev/null || true