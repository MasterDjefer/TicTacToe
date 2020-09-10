#include "geometry.h"

bool Geometry::isBelongTo(const QPoint &cell, int cellSize, const QPoint &point)
{
    int x1 = cell.x();
    int y1 = cell.y();
    int x2 = cell.x() + cellSize;
    int y2 = cell.y();
    int x3 = cell.x() + cellSize;
    int y3 = cell.y() + cellSize;
    int x4 = cell.x();
    int y4 = cell.y() + cellSize;

    int x = point.x();
    int y = point.y();

    double a = qSqrt((x1 - x2) * (x1 - x2) + (y1 - y2) * (y1 - y2));
    double a1 = qSqrt((x1 - x) * (x1 - x) + (y1 - y) * (y1 - y));
    double b1 = qSqrt((x - x2) * (x - x2) + (y - y2) * (y - y2));
    double b = qSqrt((x3 - x2) * (x3 - x2) + (y3 - y2) * (y3 - y2));
    double c1 = qSqrt((x - x3) * (x - x3) + (y - y3) * (y - y3));
    double c = qSqrt((x4 - x3) * (x4 - x3) + (y4 - y3) * (y4 - y3));
    double d1 = qSqrt((x4 - x) * (x4 - x) + (y4 - y) * (y4 - y));
    double d = qSqrt((x4 - x1) * (x4 - x1) + (y4 - y1) * (y4 - y1));

    double p1 = (a + a1 + b1) / 2.0;
    double p2 = (b + b1 + c1) / 2.0;
    double p3 = (c + c1 + d1) / 2.0;
    double p4 = (d + d1 + a1) / 2.0;

    double s1 = qSqrt(p1 * (p1 - a) * (p1 - a1) * (p1 - b1));
    double s2 = qSqrt(p2 * (p2 - b) * (p2 - b1) * (p2 - c1));
    double s3 = qSqrt(p3 * (p3 - c) * (p3 - c1) * (p3 - d1));
    double s4 = qSqrt(p4 * (p4 - d) * (p4 - d1) * (p4 - a1));
    double s = cellSize * cellSize;

    if ((qRound((s1 + s2 + s3 + s4) * 1000)) / 1000.0 <= s)
        return true;
    else
        return false;
}
