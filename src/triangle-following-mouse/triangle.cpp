#include "triangle.hpp"
#include <raylib.h>
#include <raymath.h>
#include <iostream>
#include <math.h>

Triangle::Triangle(int x, int y, float triangleSize, Color triangleColor, bool triangleShowCentroid)
{
    originalPosition = {(float)x, (float)y};
    position = {0, 0}; // set to original position at end of constructor

    originalAngle = -PI / 2.f; // starting angle. points towards +x axis
    rotatedAngle = 0.f;        // set to original rotation at end of constructor

    size = triangleSize;
    color = triangleColor;
    showCentroid = triangleShowCentroid;

    angleFromHeightVector = PI / 4.f;                      // determins the pointy-ness of the triangle
    float height = 2 * size * cosf(angleFromHeightVector); // constraining element of the triangle
    basisOrientation = {
        {(0.0f * size), (1.0f * height)},                                               // POINT A
        {(sinf(angleFromHeightVector) * size), (-cosf(angleFromHeightVector) * size)},  // POINT B
        {(sinf(angleFromHeightVector) * -size), (cosf(angleFromHeightVector) * -size)}, // POINT C
    };
    orientation = basisOrientation; // A() B() C()
    vertices = basisOrientation;

    // because of how the triangle is constructed, the centroid is always equal to the position
    centroid = {(1 / 3.f) * (vertices.a.x + vertices.b.x + vertices.c.x),
                (1 / 3.f) * (vertices.a.y + vertices.b.y + vertices.c.y)};

    triangleDir = Vector2Normalize(Vector2Subtract(vertices.a, centroid));
    SetTrianglePosition(originalPosition);
    SetTriangleRotation(originalAngle);
};

void Triangle::Draw()
{
    DrawTriangle(vertices.a, vertices.b, vertices.c, color);
    if (showCentroid) // for centroid
    {
        DrawCircleLines((int)centroid.x, (int)centroid.y, size / 20.f + 1.f, WHITE);
        DrawCircle((int)centroid.x, (int)centroid.y, size / 20.f, BLACK);
    }
};

void Triangle::UpdateTriangleColor(Color newColor)
{
    color = newColor;
}

void Triangle::UpdateTriangleSize(float newSize)
{
    float height = 2 * size * cosf(angleFromHeightVector); // constraining element of the triangle
    basisOrientation = {
        {(0.0f * newSize), (1.0f * height)},                                                  // POINT A
        {(sinf(angleFromHeightVector) * newSize), (-cosf(angleFromHeightVector) * newSize)},  // POINT B
        {(sinf(angleFromHeightVector) * -newSize), (cosf(angleFromHeightVector) * -newSize)}, // POINT C
    };
    orientation = basisOrientation; // A() B() C()
}

void Triangle::SetTrianglePosition(Vector2 newPos)
{
    position = newPos;
    centroid = newPos;

    orientation.a.x = orientation.a.x;
    orientation.a.y = orientation.a.y;

    vertices.a = Vector2Add(newPos, orientation.a);
    vertices.b = Vector2Add(newPos, orientation.b);
    vertices.c = Vector2Add(newPos, orientation.c);

    // centroid = {(1 / 3.f) * (vertices.a.x + vertices.b.x + vertices.c.x),
    //             (1 / 3.f) * (vertices.a.y + vertices.b.y + vertices.c.y)};

    triangleDir = Vector2Normalize(Vector2Subtract(vertices.a, centroid));
};

void Triangle::MoveTriangle(float x, float y)
{
    SetTrianglePosition(Vector2{position.x + x, position.y + y});
};

void Triangle::ResetTrianglePosition()
{
    SetTrianglePosition(originalPosition);
}

void Triangle::SetTriangleRotation(float angle)
{
    rotatedAngle = angle;
    auto rotateFromBasis = [&](Vector2 const &basisVector, Vector2 &vector)
    {
        vector.x = basisVector.x * cosf(angle) - basisVector.y * sinf(angle);
        vector.y = basisVector.x * sinf(angle) + basisVector.y * cosf(angle);
    };

    rotateFromBasis(basisOrientation.a, orientation.a);
    rotateFromBasis(basisOrientation.b, orientation.b);
    rotateFromBasis(basisOrientation.c, orientation.c);
    // SetTrianglePosition(position);
};

void Triangle::RotateTriangle(float angle)
{
    // std::cout << "Rotation: " << angle << '\n';
    if (abs(angle) > 0.01)
    {
        rotatedAngle += angle;
    };
    SetTriangleRotation(rotatedAngle);
};

void Triangle::ResetTriangleRotation()
{
    SetTriangleRotation(originalAngle);
};

void Triangle::RotateToVector(Vector2 vector)
{
    vector = Vector2Normalize(Vector2Subtract(vector, centroid));
    RotateTriangle(atan2(triangleDir.x * vector.y - vector.x * triangleDir.y,
                         triangleDir.x * vector.x + triangleDir.y * vector.y)); // atan(cross/dot) = theta
};
