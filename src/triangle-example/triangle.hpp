#pragma once
#include <raylib.h>

class Triangle
{

private:
    struct Vertices
    {
        Vector2 a;
        Vector2 b;
        Vector2 c;
    };

public:
    float size;
    float angleFromHeightVector;
    Color color;
    Vector2 position;
    Vector2 velocity;
    Vector2 acceleration;
    Vector2 centroid;

    Vertices vertices;
    Vertices orientation;

    Vertices baseOrientation;
    Vector2 triangleDir;

    Triangle(int w, int h);
    void Draw();
    void SetTrianglePosition(Vector2 newPos);
    void MoveTriangle(float x, float y);
    void SetTriangleRotation(float angle);
    void RotateTriangle(float angle);
};
