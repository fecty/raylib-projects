#pragma once
#include <raylib.h>

class Circle
{
public:
    Vector2 position;
    float radius;
    Color color;

    Circle(int w, int h);
    void CircleMove(Vector2 newPos);
    void CircleDraw();
};

class Square
{
public:
    Vector2 position;
    float size;
    Color color;

    Square(int w, int h);
    void SquareMove(Vector2 newPos);
    void SquareDraw();
    void isCollision(bool collision);
};