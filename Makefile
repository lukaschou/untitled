# Compiler and flags
CC = gcc
CFLAGS = -Wall -Wextra -Iinclude

# Project name
TARGET = game

# Source and object files
SRCDIR = src
OBJDIR = obj
INCDIR = include

SOURCES := $(wildcard $(SRCDIR)/*.c)
OBJECTS := $(patsubst $(SRCDIR)/%.c,$(OBJDIR)/%.o,$(SOURCES))

# Main file
MAIN = game.c

# Default rule
all: $(TARGET)

# Link the target executable
$(TARGET): $(OBJECTS) $(MAIN)
	$(CC) $(CFLAGS) -o $@ $^

# Compile .c to .o
$(OBJDIR)/%.o: $(SRCDIR)/%.c | $(OBJDIR)
	$(CC) $(CFLAGS) -c $< -o $@

# Create obj directory if it doesn't exist
$(OBJDIR):
	mkdir -p $(OBJDIR)

# Clean rule
clean:
	rm -rf $(OBJDIR) $(TARGET)

.PHONY: all clean
