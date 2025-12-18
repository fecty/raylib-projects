#include <iostream>
#include <raylib.h>
#include <raymath.h>
#include "definitions.hpp"
#include "triangle.hpp"
#include <random>

using namespace std;

Vector2 calculateCenterVector(Triangle t[])
{
    Vector2 centerVector = {0, 0};
    for (int i = 0; i < TRIANGLE_NUMBERS; i++)
    {
        centerVector += (t[i].position / TRIANGLE_NUMBERS);
    }
    return centerVector;
};

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

        Vector2 centerV = calculateCenterVector(triangles);
        // Drawing Area Start
        for (int i = 0; i < TRIANGLE_NUMBERS; i++)
        {

            Triangle &t = triangles[i];
            // t.RotateToVector(mousePos);
            Vector2 TriangleToMouseV = Vector2Subtract(mousePos, t.position);
            Vector2 TriangleToCenterV = Vector2Subtract(centerV, t.position);

            t.acceleration = Vector2Normalize(TriangleToMouseV) * TRIANGLE_ACCELERATION_FACTOR;

            // Triangle Separation from other Triangles
            for (int j = 0; j < TRIANGLE_NUMBERS; j++)
            {
                Triangle &other = triangles[j];
                Vector2 TriangleToOtherV = Vector2Subtract(other.position, t.position);
                t.acceleration += Vector2Normalize(TriangleToOtherV) * -TRIANGLE_SEPARATION_FACTOR;
            }

            t.velocity *= TRIANGLE_VELOCITY_FRICTION_FACTOR;
            // t.acceleration += Vector2Normalize(TriangleToCenterV) * -1 * (10000 / Vector2Length(TriangleToCenterV));
            t.velocity += t.acceleration * dt; // v_f = v_i + a*dt
            t.position += t.velocity * dt;     // x_f = x_i + v*dt

            t.RotateToVector(Vector2Subtract(mousePos, t.velocity * -1));
            t.SetTrianglePosition({t.position.x, t.position.y});

            DrawCircleLines(centerV.x, centerV.y, 5, RED); // center vector of all triangles
            t.Draw();
        }

        DrawCircleLines((int)mousePos.x, (int)mousePos.y, 5, WHITE);

        // Drawing Area End
        EndDrawing();
    }

    CloseWindow();

    return 0;
}