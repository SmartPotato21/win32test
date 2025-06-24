# Compiler and flags
CXX = g++
CXXFLAGS = -Wextra -std=c++17 -mwindows
LDFLAGS = -luser32 -lgdi32 -lopengl32

# Target executable
TARGET = WinMain

# Source files
SRC = main.cpp basic_constructor.cpp

# Default target to build the executable
all: $(TARGET)

$(TARGET): $(SRC)
	$(CXX) $(CXXFLAGS) -o $(TARGET) $(SRC) $(LDFLAGS)

# Run the program
run: $(TARGET)
	./$(TARGET)

# Clean up build artifacts
clean:
	rm -f $(TARGET)
