# 🧰 Setup Raylib + MSYS2 (UCRT64) no Windows

## 1. Instalar o MSYS2
Baixe e instale:
https://www.msys2.org/

---

## 2. Abrir o terminal correto
Abra o terminal:

**MSYS2 UCRT64**

---

## 3. Instalar GCC + Toolchain (make, gdb, etc)

```bash
pacman -S mingw-w64-ucrt-x86_64-toolchain
```

---

## 4. Instalar Raylib

```bash
pacman -S mingw-w64-ucrt-x86_64-raylib
```

---

## 5. (Opcional) Configurar PATH

Só necessário se você quiser usar fora do MSYS2:

Adicionar ao PATH do Windows:
```
C:\msys64\ucrt64\bin
```

Também é recomendado remover versões antigas do GCC para evitar conflitos.

---

## 6. Código de teste

### main.c
```c
#include "raylib.h"

int main(void) {
    InitWindow(800, 450, "raylib funcionando");

    while (!WindowShouldClose()) {
        BeginDrawing();
        ClearBackground(RAYWHITE);
        DrawText("Hello, raylib!", 300, 200, 20, DARKGRAY);
        EndDrawing();
    }

    CloseWindow();
    return 0;
}
```

---

## 7. Makefile

```make
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
```

---

## 8. Rodar o projeto

No terminal UCRT64:

```bash
mingw32-make run
```

---

## 9. Dica para VSCode

Se aparecer erro no `#include "raylib.h"`:

Configure o includePath no `c_cpp_properties.json`:

```
C:/msys64/ucrt64/include
```

---

## ✅ Pronto!
Agora você tem um ambiente funcional com Raylib no Windows usando MSYS2 🚀
