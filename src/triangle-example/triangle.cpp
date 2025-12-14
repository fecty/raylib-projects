#include "triangle.hpp"
#include <raylib.h>
#include <iostream>
#include <math.h>

Triangle::Triangle(int w, int h)
{
    pos = {w / 2.f, h / 2.f};
    color = RED;
    size = 100;

    baseOrientation = {
        {(0.0f * size), (0.0f * size)},
        {(0.0f * size), (1.0f * size)},
        {(2.0f * size), (0.5f * size)},
    };
    orientation = baseOrientation;

    Vector2 horz = {0, 1};

    v = orientation;
    SetTrianglePosition(pos);
    // centroid = {(1 / 3.f) * (v.a.x + v.b.x + v.c.x), (1 / 3.f) * (v.a.y + v.b.y + v.c.y)};
    centroid = {(1 / 3.f) * (orientation.a.x + orientation.b.x + orientation.c.x), (1 / 3.f) * (orientation.a.y + orientation.b.y + orientation.c.y)};

    pos = {w / 2.f, h / 2.f};
    color = RED;
    25
}

void Triangle::Draw()
{

    // std::cout << v.a.x << ' ' << v.a.y << "\t\t";
    // std::cout << v.b.x << ' ' << v.b.y << "\t\t";
    // std::cout << v.c.x << ' ' << v.c.y << '\n';

    DrawTriangle(v.a, v.b, v.c, color);

    // DrawCircle(centroid.x, centroid.y, 10.f, BLACK);
    // DrawTriangle(orientation.a, orientation.b, orientation.c, {255, 0, 0, 100});
}

void Triangle::SetTrianglePosition(Vector2 newPos)
{
    v.a.x = newPos.x + orientation.a.x;
    v.a.y = newPos.y + orientation.a.y;

    v.b.x = newPos.x + orientation.b.x;
    v.b.y = newPos.y + orientation.b.y;

    v.c.x = newPos.x + orientation.c.x;
    v.c.y = newPos.y + orientation.c.y;
    centroid = {(1 / 3.f) * (orientation.a.x + orientation.b.x + orientation.c.x), (1 / 3.f) * (orientation.a.y + orientation.b.y + orientation.c.y)};
}

void Triangle::MoveTriangle(float x, float y)
{
}

void Triangle::RotateTriangle(float angle)
{

    std::cout << angle << '\n';

    Vector2 g = centroid;

    float cosA = cosf(angle);
    float sinA = sinf(angle);

    auto rotateFromBase = [&](const Vector2 &src, Vector2 &dst)
    {
        float x = src.x - g.x;
        float y = src.y - g.y;

        dst.x = x * cosA - y * sinA + g.x;
        dst.y = x * sinA + y * cosA + g.y;
    };

    rotateFromBase(baseOrientation.a, orientation.a);
    rotateFromBase(baseOrientation.b, orientation.b);
    rotateFromBase(baseOrientation.c, orientation.c);

    SetTrianglePosition(pos);
}
