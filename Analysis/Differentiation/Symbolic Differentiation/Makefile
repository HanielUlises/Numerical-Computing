CXX = g++
CXXFLAGS = -std=c++17 -Wall -Wextra -pedantic
CXXFLAGS += -O2
SRC_DIR = .
OBJ_DIR = obj
BIN_DIR = bin
SOURCES = $(SRC_DIR)/symbolic_diff.cpp $(SRC_DIR)/main.cpp
OBJECTS = $(patsubst $(SRC_DIR)/%.cpp,$(OBJ_DIR)/%.o,$(SOURCES))
EXECUTABLE = $(BIN_DIR)/symbolic_diff

all: $(EXECUTABLE)

$(EXECUTABLE): $(OBJECTS) | $(BIN_DIR) 
    $(CXX) $(OBJECTS) -o $@ $(CXXFLAGS)

$(OBJ_DIR)/%.o: $(SRC_DIR)/%.cpp | $(OBJ_DIR)
    $(CXX) -c $< -o $@ $(CXXFLAGS)

$(BIN_DIR):
    mkdir -p $(BIN_DIR)

$(OBJ_DIR):
    mkdir -p $(OBJ_DIR)

clean:
    rm -rf $(OBJ_DIR) $(BIN_DIR)

run: $(EXECUTABLE)
    ./$(EXECUTABLE)

rebuild: clean all

.PHONY: all clean run rebuild