#define RAYGUI_IMPLEMENTATION
#include "raylib.h"
#include "raygui.h"
#include <stdio.h>

int originalTextSize;
void textSizeSave();
void textSizeSet(int x);
void textSizeRestore();

void textSizeSave()
{
    // 1. Get the original text size so we can restore it
    originalTextSize = GuiGetStyle(DEFAULT, TEXT_SIZE);
}
void textSizeSet(int x)
{
    // 2. Set the new, larger text size
    GuiSetStyle(DEFAULT, TEXT_SIZE, x);
}
void textSizeRestore()
{
    // 4. IMPORTANT: Restore the original text size for any other controls
    GuiSetStyle(DEFAULT, TEXT_SIZE, originalTextSize);
}

int main() {
    SetConfigFlags(FLAG_WINDOW_RESIZABLE);
    InitWindow(720,720,"Developer Mode");

    Font myFont = LoadFontEx("fonts/baloo2.ttf", 280, 0, 0);
    GuiSetFont(myFont);

    if (myFont.texture.id == 0) {
        printf("WARNING: Font could not be loaded. Using default font.\n");
        myFont = GetFontDefault();
    }
    SetTargetFPS(60);

    // 1. Define the rectangle for our button.
    //Rectangle b1 = { 260, 150, 250, 80 };
    //Rectangle b2 = { 260, 280, 250, 50 };
    

    bool button1Clicked = false;
    bool button2Clicked = false;

    // Set the default text size for most controls
    GuiSetStyle(DEFAULT, TEXT_SIZE, 40);

    while(!WindowShouldClose()  )
    {
        float buttonWidth = GetScreenWidth() * 0.4f;
        Rectangle b1 = { (GetScreenWidth() - buttonWidth) / 2.0f, GetScreenHeight() * 0.3f, buttonWidth, GetScreenHeight() * 0.15f };
        Rectangle b2 = { (GetScreenWidth() - buttonWidth) / 2.0f, GetScreenHeight() * 0.5f, buttonWidth, GetScreenHeight() * 0.1f };
        BeginDrawing();
        ClearBackground(GRAY);

        textSizeSave();
        textSizeSet(50);
        // --- Draw the first button using the default text size (20) ---
        if (GuiButton(b1, "Resized Text")) {
            button1Clicked = !button1Clicked;
        }
        textSizeRestore();

        // 3. Draw the button. It will use the new size.
        if ( GuiButton(b2, "Default Size") )
        {
            button2Clicked = !button2Clicked;
        }

        if (button1Clicked) DrawTextEx(myFont, "Resized Button clicked!", (Vector2){240, 450}, 60, 1.0f, MAROON);
        if (button2Clicked) DrawTextEx(myFont, "Default Button clicked!", (Vector2){240, 480}, 60, 1.0f, MAROON);

        EndDrawing();
    }

}











/*
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
*/