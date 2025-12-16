#include <iostream>
#include <raylib.h>

#include "definitions.hpp"
#include "triangle.hpp"

using namespace std;
int main()
{
    SetTraceLogLevel(LOG_ERROR);
    InitWindow(SCREEN_WIDTH, SCREEN_HEIGHT, SCREEN_TITLE);
    SetTargetFPS(FPS);

    int w = GetScreenWidth();
    int h = GetScreenHeight();

    Triangle triangle(w, h);
    float speed = 10.f;
    float angle = 0;
    while (!WindowShouldClose())
    {

        // Event Handling
        if (IsKeyDown(KEY_A))
            triangle.MoveTriangle(-speed, 0);
        if (IsKeyDown(KEY_D))
            triangle.MoveTriangle(+speed, 0);
        if (IsKeyDown(KEY_W))
            triangle.MoveTriangle(0, -speed);
        if (IsKeyDown(KEY_S))
            triangle.MoveTriangle(0, +speed);

        // if (IsKeyDown(KEY_E))
        // {

        //     angle += -.01;
        //     triangle.RotateTriangle(angle);
        // }
        // if (IsKeyDown(KEY_Q))
        // {

        //     angle += +.01;
        //     triangle.RotateTriangle(angle);
        //         }

        // Updates

        // Drawing
        BeginDrawing();
        ClearBackground(BG_COLOR);

        triangle.Draw();

        EndDrawing();
    }

    CloseWindow();

    return 0;
}