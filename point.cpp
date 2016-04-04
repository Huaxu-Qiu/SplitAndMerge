#include "point.h"

Point::Point(int _x, int _y) : x(_x), y(_y) {}

Point Point::operator+(const Point& b) const
{
    return Point(x + b.x, y + b.y);
}

Point Point::operator-(const Point& b) const
{
    return Point(x - b.x, y - b.y);
}
