#include <iostream>
#include <raylib.h>
#include <raymath.h>
#include "definitions.hpp"
#include "triangle.hpp"

using namespace std;
int main()
{
    SetTraceLogLevel(LOG_ERROR);
    InitWindow(SCREEN_WIDTH, SCREEN_HEIGHT, SCREEN_TITLE);
    SetTargetFPS(FPS);

    float w = (float)GetScreenWidth();
    float h = (float)GetScreenHeight();

    // Main loop
    Triangle triangle((int)(w / 2.f),
                      (int)(h / 2.f),
                      100,
                      BLUE,
                      true);
    float speed = 10.f;
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

        if (IsKeyDown(KEY_E))
            triangle.RotateTriangle(.1f);
        if (IsKeyDown(KEY_Q))
            triangle.RotateTriangle(-.1f);
        if (IsKeyDown(KEY_SPACE))
        {
            triangle.ResetTrianglePosition();
            triangle.ResetTriangleRotation();
        }
        // Updates

        Vector2 mousePos = GetMousePosition();

        triangle.RotateToVector(mousePos);
        // cout << "MOUSE: \t" << "x: " << mousePos.x << "\ty: " << mousePos.y << '\n';

        // Drawing
        BeginDrawing();
        ClearBackground(BG_COLOR);

        triangle.Draw();
        DrawCircle((int)mousePos.x, (int)mousePos.y, 10, RED);

        EndDrawing();
    }

    CloseWindow();

    return 0;
}