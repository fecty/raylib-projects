#pragma once
#include <raylib.h>

struct Vertices
{
    Vector2 a;
    Vector2 b;
    Vector2 c;
};

class Triangle
{
public:
    Vector2 pos;
    Vector2 vel;
    Vector2 acc;
    Color color;
    float size;
    Vector2 centroid;
    Vertices baseOrientation;
    Vertices orientation;
    Vertices v;

    Triangle(int w, int h);
    void Draw();
    void SetTrianglePosition(Vector2 newPos);
    void MoveTriangle(float x, float y);
    void SpeedTriangle();
    void RotateTriangle(float angle);
};
