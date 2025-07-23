#define RAYGUI_IMPLEMENTATION
#include "raylib.h"
#include "raygui.h"  // Must include after raylib

int main() {
    // Init window
    InitWindow(800, 600, "Raylib GUI Window");
    SetTargetFPS(60);

    // UI state
    bool buttonClicked = false;
    char name[64] = "Hello";

    while (!WindowShouldClose()) {
        BeginDrawing();
        ClearBackground(RAYWHITE);

        // GUI Widgets
        if (GuiButton((Rectangle){ 100, 100, 120, 40 }, "Click Me")) {
            buttonClicked = true;
        }

        GuiLabel((Rectangle){ 100, 160, 200, 20 }, buttonClicked ? "Button was clicked!" : "Waiting...");

        GuiTextBox((Rectangle){ 100, 200, 200, 30 }, name, 64, true);
        GuiLabel((Rectangle){ 100, 240, 300, 20 }, TextFormat("You typed: %s", name));

        EndDrawing();
    }

    CloseWindow();
    return 0;
}
