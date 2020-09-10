#ifndef MAP_H
#define MAP_H
#include <QVector>
#include <QLine>
#include <QDebug>

class Map
{
private:
    const int mSizeBlock;
    const int mSizePen;
    QVector<QLine> mLines;
    QVector<QPoint> mCells;
    QVector<bool> mFillCells;
    QVector<bool> mFillCellsComputer;

public:
    Map(int sizeBlock, int sizePen);
    int sizeBlock() const;
    int sizePen() const;
    int formSize() const;
    int linesCount() const;
    int cellsCount() const;
    void setFilledCell(int coordinate);
    void setFilledCellComputer(int coordinate);
    QVector<QLine>* lines();
    QVector<QPoint>* cells();
    QVector<bool>* fillCells();
    QVector<bool>* fillCellsComputer();
    int countFreePlace();
    void setFalseAfterGameOver();

private:
    void setLines();
    void setCells();
    void setFalseFillCells();
};

#endif // MAP_H
