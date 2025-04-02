# Detect whether to use native or cross compiler
ifeq ($(CROSS_COMPILE),)
    CC := gcc  # Native x86_64 compiler
else
    CC := $(CROSS_COMPILE)gcc  # Cross compiler for ARM
endif

CFLAGS := -Wall -Wextra -g
TARGET := finder-app/writer
SRC := finder-app/writer.c
OBJ := finder-app/writer.o

# Default target
all: $(TARGET)

# Compile writer application
$(TARGET): $(OBJ)
	$(CC) $(CFLAGS) -o $@ $^

# Compile object files
finder-app/%.o: finder-app/%.c
	$(CC) $(CFLAGS) -c -o $@ $<

# Clean target
clean:
	rm -f $(TARGET) $(OBJ)

