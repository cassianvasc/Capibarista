CC = gcc
CFLAGS = -Wall -std=c99
LIBS = -lraylib -lopengl32 -lgdi32 -lwinmm

TARGET = main
SRC = main.c

all:
	$(CC) $(SRC) -o $(TARGET) $(CFLAGS) $(LIBS)

run: all
	./$(TARGET).exe

clean:
	rm -f *.exe

# mingw32-make run