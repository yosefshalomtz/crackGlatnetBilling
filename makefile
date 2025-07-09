# Makefile for Glatnet Billing Crack (C version)

CC = gcc
CFLAGS = -O2 -Wall
TARGET = build/kill.exe
TARGET2 = build/kill_by_WINAPI.exe
SRC = kill.c

all: $(TARGET) $(TARGET2)

$(TARGET2): kill_by_WINAPI.c
	@mkdir -p build
	$(CC) $(CFLAGS) -o $(TARGET2) kill_by_WINAPI.c

$(TARGET): $(SRC)
	@mkdir -p build
	$(CC) $(CFLAGS) -o $(TARGET) $(SRC)

clean:
	rm -rf build

run: $(TARGET)
	./build/kill.exe

.PHONY: all clean
