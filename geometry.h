#ifndef GEOMERTY_H
#define GEOMERTY_H
#include <QPoint>
#include <qmath.h>

class Geometry
{
public:
    static bool isBelongTo(const QPoint &cell, int cellSize, const QPoint &point);
};

#endif // GEOMERTY_H
