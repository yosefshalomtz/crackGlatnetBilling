# Makefile for Glatnet Billing Crack (C version)

CC = gcc
CFLAGS = -O2 -Wall
TARGET = build/kill.exe
SRC = kill.c

all: $(TARGET)

$(TARGET): $(SRC)
	@mkdir -p build
	$(CC) $(CFLAGS) -o $(TARGET) $(SRC)

clean:
	rm -rf build

run: $(TARGET)
	./build/kill.exe

.PHONY: all clean
