# Compiler to use
CC = gcc

# Compiler flags
CFLAGS = -Wall -Wextra -g

# Target executable name
TARGET = database

# Source files
SOURCES = src/main.c src/btree.c src/table.c src/input.c src/repl.c

# Object files
OBJECTS = $(SOURCES:.c=.o)

# Default target
all: $(TARGET)

# Link the target executable
$(TARGET): $(OBJECTS)
	$(CC) $(CFLAGS) -o $(TARGET) $(OBJECTS)

# Compile source files to object files
%.o: %.c
	$(CC) $(CFLAGS) -c $< -o $@

# Clean up build files
clean:
	rm -f $(OBJECTS) $(TARGET)

# Phony targets
.PHONY: all clean
