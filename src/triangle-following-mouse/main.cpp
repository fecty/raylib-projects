#include <iostream>
#include <raylib.h>
#include <raymath.h>
#include "definitions.hpp"
#include "triangle.hpp"
#include <random>

using namespace std;
int main()
{
    SetTraceLogLevel(LOG_ERROR);
    SetConfigFlags(FLAG_WINDOW_TRANSPARENT);
    InitWindow(SCREEN_WIDTH, SCREEN_HEIGHT, SCREEN_TITLE);
    SetTargetFPS(FPS);

    float w = (float)GetScreenWidth();
    float h = (float)GetScreenHeight();

    // Main loop

    std::mt19937 rng{std::random_device{}()};
    std::uniform_real_distribution<float> dist(0.0f, 1.0f);

    Triangle triangles[TRIANGLE_NUMBERS]; // Define multiple objects of Triangle class
    const Color COLORS[TRIANGLE_MAX_COLORS] = {RED, BLUE, ORANGE, GREEN, YELLOW, MAGENTA, WHITE};
    for (int i = 0; i < TRIANGLE_NUMBERS; i++) // Preconfigure all triangle objects with base settings
    {
        Triangle &t = triangles[i];

        t.velocity = {dist(rng) * TRIANGLE_INITIAL_MAX_VELOCITY,
                      dist(rng) * TRIANGLE_INITIAL_MAX_VELOCITY};
        t.SetTrianglePosition({dist(rng) * w,
                               dist(rng) * h});
        t.UpdateTriangleColor(COLORS[(int)floor(dist(rng) * TRIANGLE_MAX_COLORS)]);
    }

    float dt;
    while (!WindowShouldClose())
    {

        // Event Handling

        // Updates
        dt = GetFrameTime();
        Vector2 mousePos = GetMousePosition();

        // Drawing
        BeginDrawing();
        ClearBackground({0, 0, 0, 100});

        // Drawing Area Start
        for (int i = 0; i < TRIANGLE_NUMBERS; i++)
        {

            Triangle &t = triangles[i];
            // t.RotateToVector(mousePos);
            Vector2 TriangleToMouseV = Vector2Subtract(GetMousePosition(), t.position);

            t.acceleration = Vector2Normalize(TriangleToMouseV) * TRIANGLE_ACCELERATION_FACTOR;
            t.velocity += t.acceleration * dt; // v_f = v_i + a*dt
            t.velocity *= TRIANGLE_VELOCITY_FRICTION_FACTOR;
            t.position += t.velocity * dt; // x_f = x_i + v*dt

            t.RotateToVector(Vector2Subtract(mousePos, t.velocity * -1));
            t.SetTrianglePosition({t.position.x, t.position.y});
            t.Draw();
        }
        DrawCircle((int)mousePos.x, (int)mousePos.y, 10, RED);

        // Drawing Area End
        EndDrawing();
    }

    CloseWindow();

    return 0;
}