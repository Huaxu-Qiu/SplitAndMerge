#include "splitandmerge.h"
#include <cmath>

std::vector<Point> splitandmerge(std::vector<Point> points, float threshold, float collinearity)
{
    std::vector<Point> endPoints;
    endPoints.push_back(points.front());
    split(points, threshold, endPoints);
    endPoints.push_back(points.back());
    merge(endPoints, collinearity);
    return endPoints;
}

std::vector<std::vector<Point> > SplitAndMergeGap(std::vector<Point> points, float threshold, int gapsize, float collinearity)
{
    std::vector<std::vector<Point> > segments;
    std::vector<int> segmentEndpoints;
    for (int i = 0; i < points.size() - 1; i++)
    {
        if (distanceFromPointToPoint(points[i], points[i + 1]) >= gapsize)
        {
            segmentEndpoints.push_back(i + 1);
        }
    }
    segmentEndpoints.push_back(points.size());

    for (int i = 0; i < segmentEndpoints.size(); i++)
    {
        std::vector<Point>::iterator start = (i == 0) ? points.begin() : points.begin() + segmentEndpoints.at(i - 1);
        std::vector<Point>::iterator stop = points.begin() + segmentEndpoints.at(i);
        std::vector<Point> segment_points = std::vector<Point>(start, stop);
        std::vector<Point> segment = splitandmerge(segment_points, threshold, collinearity);
        segments.push_back(segment);
    }

    return segments;
}

void split(std::vector<Point> points, float threshold, std::vector<Point>& splits)
{
    Line line(points.front(), points.back());
    int index = mostDistantPoint(points, line);
    if (index >= 0 && distanceFromPointToLine(points.at(index), line) > threshold)
    {
        if (index + 1 < points.size())
        {
            std::vector<Point>::const_iterator begin = points.begin();
            std::vector<Point>::const_iterator stop = points.begin() + index + 1;
            std::vector<Point> subline = std::vector<Point>(begin, stop);
            split(subline, threshold, splits);
        }

        splits.push_back(points.at(index));

        if (index + 1 < points.size())
        {
            std::vector<Point>::const_iterator begin = points.begin() + index;
            std::vector<Point>::const_iterator stop = points.end();
            std::vector<Point> subline = std::vector<Point>(begin, stop);
            split(subline, threshold, splits);
        }
    }
}

void merge(std::vector<Point>& splits, float collinearity)
{
    std::vector<int> indicesToMerge;
    for (std::size_t i = 0; i < splits.size() - 2; i++)
    {
        Line l1(splits.at(i), splits.at(i + 1));
        Line l2(splits.at(i + 1), splits.at(i + 2));
        float angle = angleBetweenLines(l1, l2);
        if (std::abs(angle) < collinearity)
        {
            indicesToMerge.push_back(i + 1);
        }
    }
    for (std::size_t i = 0; i < indicesToMerge.size(); i++)
    {
        splits.erase(splits.begin() + indicesToMerge.at(i));
    }
}

float angleBetweenLines(Line l1, Line l2)
{
    return atan((l2.a - l1.a)/(1 + l1.a*l2.a));
}

float distanceFromPointToLine(Point point, Line line)
{
    return std::abs(-line.a*point.x + point.y - line.b)/sqrt(line.a*line.a + 1);
}

float distanceFromPointToPoint(Point p1, Point p2)
{
    return sqrt((p2.x - p1.x)*(p2.x - p1.x) + (p2.y - p1.y)*(p2.y - p1.y));
}

int mostDistantPoint(std::vector<Point> points, Line line)
{
    int index = -1;
    float longestDistance = 0;
    for (std::size_t i = 0; i < points.size(); i++)
    {
        float distance = distanceFromPointToLine(points.at(i), line);
        if (distance > longestDistance)
        {
            longestDistance = distance;
            index = i;
        }
    }
    return index;
}
