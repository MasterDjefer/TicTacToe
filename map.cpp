#include "map.h"

Map::Map(int sizeBlock, int sizePen) : mSizeBlock(sizeBlock), mSizePen(sizePen)
{
    setLines();
    setCells();
    setFalseFillCells();
}

int Map::sizeBlock() const
{
    return mSizeBlock;
}

int Map::sizePen() const
{
    return mSizePen;
}

int Map::formSize() const
{
    return mSizeBlock * 3 + mSizePen * 2;
}

int Map::linesCount() const
{
    return mLines.size();
}

int Map::cellsCount() const
{
    return mCells.size();
}

void Map::setFilledCell(int coordinate)
{
    mFillCells.replace(coordinate, true);
}

void Map::setFilledCellComputer(int coordinate)
{
    mFillCellsComputer.replace(coordinate, true);
}

QVector<QLine> *Map::lines()
{
    return &mLines;
}

QVector<QPoint> *Map::cells()
{
    return &mCells;
}

QVector<bool> *Map::fillCells()
{
    return &mFillCells;
}

QVector<bool> *Map::fillCellsComputer()
{
    return &mFillCellsComputer;
}

int Map::countFreePlace()
{
    int countFreeCells = 0;
    for (int i = 0; i < mFillCells.size(); ++i)
    {
        if (mFillCells.at(i))
            countFreeCells++;
        if (mFillCellsComputer.at(i))
            countFreeCells++;
    }
    return mFillCells.size() - countFreeCells;
}

void Map::setLines()
{
    mLines.push_back(QLine(0, mSizeBlock + mSizePen / 2,
                           mSizeBlock * 3 + mSizePen * 2, mSizeBlock + mSizePen / 2));
    mLines.push_back(QLine(0, mSizeBlock * 2 + mSizePen * 1.5,
                           mSizeBlock * 3 + mSizePen * 2, mSizeBlock * 2 + mSizePen * 1.5));
    mLines.push_back(QLine(mSizeBlock + mSizePen / 2, 0,
                           mSizeBlock + mSizePen / 2, mSizeBlock * 3 + mSizePen * 2));
    mLines.push_back(QLine(mSizeBlock * 2 + mSizePen * 1.5, 0,
                           mSizeBlock * 2 + mSizePen * 1.5, mSizeBlock * 3 + mSizePen * 2));
}

void Map::setCells()
{
    for (int i = 0; i < 3; ++i)
        mCells.push_back(QPoint(i * mSizeBlock + mSizePen * i, 0));
    for (int i = 0; i < 3; ++i)
        mCells.push_back(QPoint(i * mSizeBlock + mSizePen * i, mSizeBlock + mSizePen));
    for (int i = 0; i < 3; ++i)
        mCells.push_back(QPoint(i * mSizeBlock + mSizePen * i, mSizeBlock * 2 + mSizePen * 2));
}

void Map::setFalseFillCells()
{
    for (int i = 0; i < 9; ++i)
    {
        mFillCells.push_back(false);
        mFillCellsComputer.push_back(false);
    }
}

void Map::setFalseAfterGameOver()
{
    for (int i = 0; i < 9; ++i)
    {
        mFillCells.replace(i, false);
        mFillCellsComputer.replace(i, false);
    }
}
