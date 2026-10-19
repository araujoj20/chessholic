# C++ compiler used to build the project.
CXX := g++

# Compiler options: C++17, warnings, and the project include directory.
CXXFLAGS := -std=c++17 -Wall -Wextra -Wpedantic -Icode/inc

# SDL compiler and linker flags provided by pkg-config.
SDL_FLAGS := $(shell pkg-config --cflags --libs sdl2 SDL2_image)

# Name of the final executable.
TARGET := chessholic

# Directory where compiled object files are stored.
BUILD_DIR := build

# Find all C++ source files in the source directory.
SOURCES := $(shell find code/src -type f \( -name '*.cpp'\))

# Convert source paths into matching object-file paths inside build/.
OBJECTS := $(patsubst code/src/%,$(BUILD_DIR)/%,$(SOURCES))
OBJECTS := $(OBJECTS:.cpp=.o)
OBJECTS := $(OBJECTS:.c++=.o)

# Targets that do not represent files.
.PHONY: all run clean

# Default target: build the executable.
all: $(TARGET)

# Link all object files and SDL libraries into the final executable.
$(TARGET): $(OBJECTS)
	$(CXX) $(OBJECTS) $(SDL_FLAGS) -o $@

# Compile .cpp source files into object files.
$(BUILD_DIR)/%.o: code/src/%.cpp
	@mkdir -p $(dir $@)
	$(CXX) $(CXXFLAGS) -c $< -o $@

# Build the executable if needed, then run it.
run: $(TARGET)
	SDL_VIDEO_X11_FORCE_EGL=1 ./$(TARGET)

# Remove generated object files and the executable.
clean:
	rm -rf $(BUILD_DIR) $(TARGET)
