#ifndef POINT_H
#define POINT_H

class Point
{
    public:
    int x;
    int y;
    Point(int, int);
    Point operator+(const Point& b) const;
    Point operator-(const Point& b) const;
};

#endif // POINT_H
