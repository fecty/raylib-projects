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

    Vertices basisOrientation;
    Vector2 originalPosition;
    float angleFromHeightVector;
    float originalAngle;
    bool showCentroid;

public:
    float size;
    Color color;
    Vector2 position;
    Vector2 velocity;
    Vector2 acceleration;
    float rotatedAngle;
    Vector2 centroid;
    Vertices vertices;
    Vertices orientation;
    Vector2 triangleDir;

    Triangle(int x, int y, float triangleSize, Color triangleColor, bool triangleShowCentroid = false);
    void Draw();
    void SetTrianglePosition(Vector2 newPos);
    void MoveTriangle(float x, float y);
    void ResetTrianglePosition();

    void SetTriangleRotation(float angle);
    void RotateTriangle(float angle);
    void ResetTriangleRotation();
    void RotateToVector(Vector2 vector);
};
