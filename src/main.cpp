#include "raylib.h"

int main() {
  SetConfigFlags(FLAG_VSYNC_HINT | FLAG_WINDOW_HIGHDPI);
  InitWindow(800, 600, "Axle Engine");
  SetTargetFPS(60);

  while (!WindowShouldClose()) {
    BeginDrawing();
    ClearBackground(RAYWHITE);
    DrawText("Welcome to Axle Engine!", 10, 10, 30, GRAY);
    EndDrawing();
  }

  CloseWindow();
  return 0;
}