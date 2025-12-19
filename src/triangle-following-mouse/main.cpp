#include <iostream>
#include <random>
#include <raylib.h>
#include <raymath.h>
#include "definitions.hpp"
#include "triangle.hpp"

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

Vector2 calculateSumVelocity(Triangle t[])
{
    Vector2 velocityVector = {0, 0};
    for (int i = 0; i < TRIANGLE_NUMBERS; i++)
    {
        velocityVector += (t[i].velocity / TRIANGLE_NUMBERS);
    }
    return velocityVector;
};

bool IsOnScreen(Vector2 p)
{
    return p.x >= 0.f &&
           p.x <= (float)GetScreenWidth() &&
           p.y >= 0.f &&
           p.y <= (float)GetScreenHeight();
}

int main()
{
    SetTraceLogLevel(LOG_ERROR);
    SetConfigFlags(FLAG_WINDOW_TRANSPARENT);
    InitWindow(SCREEN_WIDTH, SCREEN_HEIGHT, SCREEN_TITLE);
    // InitWindow(GetMonitorWidth(GetCurrentMonitor()), GetMonitorHeight(GetCurrentMonitor()), SCREEN_TITLE);
    // ToggleFullscreen();
    SetTargetFPS(FPS);

    float w = (float)GetScreenWidth();
    float h = (float)GetScreenHeight();

    // Main loop

    std::mt19937 rng{std::random_device{}()};
    std::uniform_real_distribution<float> dist(0.0f, 1.0f);

    Triangle triangles[TRIANGLE_NUMBERS]; // Define multiple objects of Triangle class

    // const Color COLORS[TRIANGLE_MAX_COLORS] = {RED, BLUE, ORANGE, GREEN, YELLOW, MAGENTA, WHITE};

    int alphaFactor = 0;
    Color COLORS[TRIANGLE_MAX_COLORS] = {
        {255, 20, 147, 255 - alphaFactor}, // neon pink
        {0, 255, 255, 255 - alphaFactor},  // neon cyan
        {57, 255, 20, 255 - alphaFactor},  // neon green
        {255, 255, 0, 255 - alphaFactor},  // neon yellow
        {255, 69, 0, 255 - alphaFactor},   // neon orange
        {138, 43, 226, 255 - alphaFactor}, // neon purple
        {0, 191, 255, 255 - alphaFactor},  // electric blue
        {255, 0, 0, 255 - alphaFactor},    // neon red
        {50, 255, 126, 255 - alphaFactor}, // neon mint
        {255, 0, 255, 255 - alphaFactor}   // neon magenta
    };

    for (int i = 0; i < TRIANGLE_NUMBERS; i++) // Preconfigure all triangle objects with base settings
    {
        Triangle &t = triangles[i];

        t.velocity = {dist(rng) * TRIANGLE_INITIAL_MAX_VELOCITY,
                      dist(rng) * TRIANGLE_INITIAL_MAX_VELOCITY};
        t.SetTrianglePosition({dist(rng) * w,
                               dist(rng) * h});
        t.UpdateTriangleColor(COLORS[(int)floor(dist(rng) * TRIANGLE_MAX_COLORS)]); // looks colorful
        // t.UpdateTriangleColor({255, 255, 255, 100}); // looks ghoulish
    }

    float dt;
    while (!WindowShouldClose())
    {

        // Event Handling

        // Updates
        dt = GetFrameTime();
        Vector2 mousePos = GetMousePosition();
        int trianglesOnscreen = 0;
        float offScreenForceFactor = 1.f;

        // Drawing
        BeginDrawing();
        ClearBackground({0, 0, 0, 150});

        Vector2 centerV = calculateCenterVector(triangles);
        Vector2 sumVelocityV = Vector2Normalize(calculateSumVelocity(triangles)) * 100 + centerV;
        // cout << "X: " << sumVelocityV.x << "\t Y: " << sumVelocityV.y << '\n';

        // Drawing Area Start
        for (int i = 0; i < TRIANGLE_NUMBERS; i++)
        {

            Triangle &t = triangles[i];

            Vector2 TriangleToMouseV = Vector2Subtract(mousePos, t.position);
            Vector2 TriangleToCenterV = Vector2Subtract(centerV, t.position);
            Vector2 TriangleToSumVelocityV = Vector2Subtract(sumVelocityV, t.position);

            offScreenForceFactor = IsOnScreen(t.position) ? 1.0f : 2.0f; // double acceleration when t is offscreen
            t.acceleration = Vector2Normalize(TriangleToMouseV) * TRIANGLE_ACCELERATION_FACTOR * offScreenForceFactor;

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

            DrawCircleLines((int)centerV.x, (int)centerV.y, 10, RED);            // center vector of all triangles
            DrawCircleLines((int)sumVelocityV.x, (int)sumVelocityV.y, 10, BLUE); // center vector of all triangles

            if (IsOnScreen(t.position))
                trianglesOnscreen++;
            t.Draw();
        }
        // DrawText(TextFormat("Total Triangles: %d", TRIANGLE_NUMBERS), 5, 5, 20, WHITE);
        DrawText(TextFormat("Triangles: %d/%d", TRIANGLE_NUMBERS, trianglesOnscreen), 5, 5, 20, WHITE);

        trianglesOnscreen = 0;

        DrawCircleLines((int)mousePos.x, (int)mousePos.y, 10, WHITE);

        // Drawing Area End
        EndDrawing();
    }

    CloseWindow();

    return 0;
}