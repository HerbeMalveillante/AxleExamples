#include "raylib.h"
#include "raymath.h"
#include "rlgl.h"

int main() {
  SetConfigFlags(FLAG_VSYNC_HINT | FLAG_WINDOW_HIGHDPI | FLAG_WINDOW_RESIZABLE);
  InitWindow(900, 600, "Axle Engine");
  SetTargetFPS(60);

  Camera2D camera = {{0}};
  camera.zoom = 1.0f;

  while (!WindowShouldClose()) {
    // Update
    // ============================================================

    // Translate based on mouse right click
    if (IsMouseButtonDown(MOUSE_BUTTON_LEFT)) {
      Vector2 delta = GetMouseDelta();
      delta = Vector2Scale(delta, -1.0f / camera.zoom);
      camera.target = Vector2Add(camera.target, delta);
    }

    // Zoom based on mouse wheel
    float wheel = GetMouseWheelMove();
    if (wheel != 0) {
      // Get the world point under the mouse
      Vector2 mouseWorldPos = GetScreenToWorld2D(GetMousePosition(), camera);

      // Set the offset to where the mouse is
      camera.offset = GetMousePosition();

      // Set the target to match, so that the camera maps the world space point
      // under the cursor to the screen space point under the cursor at any zoom
      camera.target = mouseWorldPos;

      // Zoom increment
      // Uses log scaling to provide consistent zoom speed
      float scale = 0.2f * wheel;
      camera.zoom = Clamp(expf(logf(camera.zoom) + scale), 0.125f, 64.0f);
    }

    // Draw
    // ============================================================
    BeginDrawing();
    ClearBackground(RAYWHITE);

    BeginMode2D(camera);
    // Draw the 3D grid, rotated 90 degrees and centered around 0,0 just so we have something in the XY plane.
    // This can be replaced with a shader later on, to render the grid.
    rlPushMatrix();
        rlTranslatef(0, 25*50, 0);
        rlRotatef(90, 1, 0, 0);
        DrawGrid(100, 50);
    rlPopMatrix();

    // Draw a reference circle
    DrawCircle(GetScreenWidth()/2, GetScreenHeight()/2, 50, MAROON);
    EndMode2D();

    // Draw mouse reference
    DrawCircleV(GetMousePosition(), 4, DARKGRAY);
    DrawTextEx(GetFontDefault(), TextFormat("[%i, %i]", GetMouseX(), GetMouseY()),
        Vector2Add(GetMousePosition(), (Vector2){-44, -23 }), 20, 2, BLACK);
    EndDrawing();
  }

  CloseWindow();
  return 0;
}
