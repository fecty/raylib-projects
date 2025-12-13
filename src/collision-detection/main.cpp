#include <iostream>
#include <raylib.h>

#include "definitions.hpp"

using namespace std;
int main()
{
    SetTraceLogLevel(LOG_ERROR);
    InitWindow(SCREEN_WIDTH, SCREEN_HEIGHT, SCREEN_TITLE);
    SetTargetFPS(FPS);

    int w = GetScreenWidth();
    int h = GetScreenHeight();

    while (!WindowShouldClose())
    {
        // Event Handling

        // Updates

        // Drawing
        BeginDrawing();
        ClearBackground(BG_COLOR);

        DrawCircle(w / 2, h / 2, 20, RED);
        EndDrawing();
    }

    CloseWindow();

    return 0;
}