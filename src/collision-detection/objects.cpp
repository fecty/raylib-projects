#include "objects.hpp"

Circle::Circle(int w, int h)
{
    position = {static_cast<float>(w) * .5f, static_cast<float>(h) * .5f};
    radius = 10.f;
    color = RED;
}
void Circle::CircleDraw()
{
    DrawCircle(static_cast<int>(position.x), static_cast<int>(position.y), radius, color);
}
void Circle::CircleMove(Vector2 newPos)
{
    position.x += newPos.x;
    position.y += newPos.y;
}

Square::Square(int w, int h)
{

    position = {static_cast<float>(w) * .5f, static_cast<float>(h) * .5f};
    // position = {100, 100};
    size = 200.f;
    color = WHITE;
}
void Square::SquareDraw()
{
    DrawRectangle(static_cast<int>(position.x - (size / 2.f)), static_cast<int>(position.y - (size / 2.f)), (int)size, (int)size, color);
}

void Square::SquareMove(Vector2 newPos)
{
    position.x += newPos.x;
    position.y += newPos.y;
}

void Square::isCollision(bool collision)
{
    if (collision)
    {
        color = {100, 100, 100, 100};
    }
    else
    {
        color = WHITE;
    }
}