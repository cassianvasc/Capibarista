#makefile para windows:
CC = gcc
CFLAGS = -Wall -std=c99 -Isrc
LIBS = -lraylib -lopengl32 -lgdi32 -lwinmm

TARGET = main
SRC = main.c src/jogo.c src/cliente.c src/lista_encadeada.c

all:
	$(CC) $(SRC) -o $(TARGET) $(CFLAGS) $(LIBS)

run: all
	./$(TARGET).exe

clean:
	rm -f *.exe

# pra rodar: mingw32-make run

#------------------------------------------------------------------------------------------------------------------------------

#makefile para linux:
# CC = gcc
# CFLAGS = -Wall -Wextra -std=c99 -Isrc
# SRC = main.c src/jogo.c src/cliente.c src/lista_encadeada.c
# OUT = game
# LIBS = -lraylib -lGL -lm -lpthread -ldl -lrt -lX11

# all:
# 	$(CC) $(CFLAGS) $(SRC) -o $(OUT) $(LIBS)

# run: all
# 	./$(OUT)

# clean:
# 	rm -f $(OUT)

#para rodar: make run