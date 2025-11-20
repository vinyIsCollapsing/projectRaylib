# Name of the executable (inside build directory)
TARGET = build/mygame

# Directories
SRCDIR = src
INCDIR = include
BUILDDIR = build

# Source files (all .cpp inside src/)
# There is no main.cpp in the root directory, only in src/
SRC = $(wildcard $(SRCDIR)/*.cpp)

# Raylib install path
RAYLIB_PATH = /usr/local

# Raylib include and lib directories
INCLUDE_DIR = $(RAYLIB_PATH)/include
LIB_DIR = $(RAYLIB_PATH)/lib

# Compiler and flags
CXX = g++
CXXFLAGS = -Wall -I$(INCDIR) -I$(INCLUDE_DIR)
LDFLAGS = -L$(LIB_DIR) -lraylib -lGL -lm -lpthread -ldl -lrt -lX11

# Object files (src/foo.cpp -> build/foo.o)
OBJECTS = $(SRC:$(SRCDIR)/%.cpp=$(BUILDDIR)/%.o)

# Default target: build the game
all: $(TARGET)

# Link the final executable
$(TARGET): $(OBJECTS)
	@mkdir -p $(dir $@)        # Ensure build/ exists
	$(CXX) $(OBJECTS) -o $(TARGET) $(LDFLAGS)

# Compile each .cpp file into .o inside build/
$(BUILDDIR)/%.o: $(SRCDIR)/%.cpp
	@mkdir -p $(dir $@)        # Create subdirectories in build/ if needed
	$(CXX) $(CXXFLAGS) -c $< -o $@

# Remove generated files
clean:
	rm -rf $(BUILDDIR) $(TARGET)

# Run the game
run: $(TARGET)
	./$(TARGET)

# Do not correspond to real files
.PHONY: all clean run
