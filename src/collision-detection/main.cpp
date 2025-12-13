#include <iostream>
#include <raylib.h>

#include "definitions.hpp"
#include "objects.hpp"

using namespace std;
int main()
{
    SetTraceLogLevel(LOG_ERROR);
    InitWindow(SCREEN_WIDTH, SCREEN_HEIGHT, SCREEN_TITLE);
    SetTargetFPS(FPS);

    int w = GetScreenWidth();
    int h = GetScreenHeight();

    Circle circle(w, h);
    Square square(w, h);
    float speed = 10.f;
    while (!WindowShouldClose())
    {
        // Event Handling
        if (IsKeyDown(KEY_LEFT))
            circle.CircleMove({-speed, 0});
        if (IsKeyDown(KEY_RIGHT))
            circle.CircleMove({+speed, 0});
        if (IsKeyDown(KEY_UP))
            circle.CircleMove({0, -speed});
        if (IsKeyDown(KEY_DOWN))
            circle.CircleMove({0, +speed});

        // Updates

        // Drawing
        BeginDrawing();

        if (CheckCollisionCircleRec(circle.position, circle.radius, {square.position.x - square.size / 2, square.position.y - square.size / 2, square.size, square.size}))
        {
            square.isCollision(true);
            cout << "true" << '\n';
        }
        else
        {
            square.isCollision(false);
        }

        ClearBackground(BG_COLOR);

        circle.CircleDraw();
        square.SquareDraw();

        EndDrawing();
    }

    CloseWindow();

    return 0;
}