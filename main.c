#include "raylib.h"

int main(void) {
    InitWindow(800, 450, "raylib funcionando");

    while (!WindowShouldClose()) {
        BeginDrawing();
        ClearBackground(RAYWHITE);
        DrawText("Hello, raylib olá!", 300, 200, 20, DARKGRAY);
        EndDrawing();
    }

    CloseWindow();
    return 0;
}