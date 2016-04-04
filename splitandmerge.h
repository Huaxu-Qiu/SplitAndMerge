#ifndef SPLITANDMERGE_H
#define SPLITANDMERGE_H

#include "point.h"
#include "line.h"
#include <vector>

std::vector<Point> splitandmerge(std::vector<Point> points, float threshold, float collinearity);
std::vector<std::vector<Point> > SplitAndMergeGap(std::vector<Point> points, float threshold, int gapsize, float collinearity);
void split(std::vector<Point> points, float threshold, std::vector<Point>& splits);
void merge(std::vector<Point>& splits, float collinearity);
float angleBetweenLines(Line l1, Line l2);
float distanceFromPointToLine(Point point, Line line);
float distanceFromPointToPoint(Point p1, Point p2);
int mostDistantPoint(std::vector<Point> points, Line line);

#endif // SPLITANDMERGE_H
