#include "widget.h"

Widget::Widget() : ifGameOverValue(false), ifRestartGame(false), myChoosing(0), myMove(true)
{
    srand(time(0));
    map = new Map(200, 10);
    this->setFixedSize(map->formSize() + 100, map->formSize());

    mChooseX = new QRadioButton("X", this);
    mChooseX->move(map->formSize() + 30, map->formSize() / 3);
    connect(mChooseX, &QRadioButton::clicked, this, &Widget::chooseX);

    mChooseO = new QRadioButton("O", this);
    mChooseO->move(map->formSize() + 30, map->formSize() / 3 + 50);
    connect(mChooseO, &QRadioButton::clicked, this, &Widget::chooseO);
}

Widget::~Widget()
{
    delete map;
    delete mChooseX;
    delete mChooseO;
}

void Widget::paintEvent(QPaintEvent *event)
{
    QPainter painter(this);

    painter.setPen(QPen(Qt::gray, map->sizePen()));
    for (int i = 0; i < map->linesCount(); ++i)
    {
        painter.drawLine(map->lines()->at(i));
    }

    painter.setPen(QPen(Qt::black, map->sizePen()));
    for (int i = 0; i < map->cellsCount(); ++i)
    {
        if (map->fillCells()->at(i))
        {
            if (myChoosing == 1)
            {
                painter.drawLine(map->cells()->at(i).x() + map->sizeBlock() / 10,
                                 map->cells()->at(i).y() + map->sizeBlock() / 10,
                                 map->cells()->at(i).x() + map->sizeBlock() - map->sizeBlock() / 10,
                                 map->cells()->at(i).y() + map->sizeBlock() - map->sizeBlock() / 10);
                painter.drawLine(map->cells()->at(i).x() + map->sizeBlock() / 10,
                                 map->cells()->at(i).y() + map->sizeBlock() - map->sizeBlock() / 10,
                                 map->cells()->at(i).x() + map->sizeBlock() - map->sizeBlock() / 10,
                                 map->cells()->at(i).y() + map->sizeBlock() / 10);
            }else
            if (myChoosing == 2)
            {
                int r = map->sizeBlock() - map->sizeBlock() / 10;
                painter.drawEllipse(map->cells()->at(i).x() + map->sizeBlock() / 2 - r / 2,
                                    map->cells()->at(i).y()  + map->sizeBlock() / 2 - r / 2,
                                    r, r);
            }
        }
    }
    for (int i = 0; i < map->cellsCount(); ++i)
    {
        if (map->fillCellsComputer()->at(i))
        {
            if (myChoosing == 1)
            {
                int r = map->sizeBlock() - map->sizeBlock() / 10;
                painter.drawEllipse(map->cells()->at(i).x() + map->sizeBlock() / 2 - r / 2,
                                    map->cells()->at(i).y()  + map->sizeBlock() / 2 - r / 2,
                                    r, r);
            }else
            if (myChoosing == 2)
            {
                painter.drawLine(map->cells()->at(i).x() + map->sizeBlock() / 10,
                                 map->cells()->at(i).y() + map->sizeBlock() / 10,
                                 map->cells()->at(i).x() + map->sizeBlock() - map->sizeBlock() / 10,
                                 map->cells()->at(i).y() + map->sizeBlock() - map->sizeBlock() / 10);
                painter.drawLine(map->cells()->at(i).x() + map->sizeBlock() / 10,
                                 map->cells()->at(i).y() + map->sizeBlock() - map->sizeBlock() / 10,
                                 map->cells()->at(i).x() + map->sizeBlock() - map->sizeBlock() / 10,
                                 map->cells()->at(i).y() + map->sizeBlock() / 10);
            }
        }
    }
}

void Widget::mousePressEvent(QMouseEvent *event)
{
    QPoint point(event->pos().x(), event->pos().y());

    if (myChoosing)
        for (int i = 0; i < map->cellsCount(); ++i)
        {
            if (Geometry::isBelongTo(map->cells()->at(i), map->sizeBlock(), point))
            {
                if (map->fillCells()->at(i) == false && map->fillCellsComputer()->at(i) == false)
                {
                    map->setFilledCell(i);
                    if (!ifGameOverValue)
                    {
                        ifGameOver();
                        if (ifRestartGame)
                        {
                            ifRestartGame = false;
                            return;
                        }
                    }
                    this->update();

                    if (map->countFreePlace())
                    {
                        computerTurn();
                        if (!ifGameOverValue)
                            ifGameOver();

                        if (ifRestartGame)
                        {
                            ifRestartGame = false;
                            return;
                        }
                    }
                    return;
                }
            }
        }
}

void Widget::computerTurn()
{
    if (computerAttack())
        return;
    if (computerDeffend())
        return;

    //////
    int coordinate = rand() % map->cellsCount();
    while (map->fillCells()->at(coordinate) || map->fillCellsComputer()->at(coordinate))
    {
        coordinate = rand() % 9;
    }

    map->setFilledCellComputer(coordinate);
}

void Widget::ifGameOver()
{
    if ((map->fillCells()->at(0) && map->fillCells()->at(1) && map->fillCells()->at(2)) ||
       (map->fillCells()->at(3) && map->fillCells()->at(4) && map->fillCells()->at(5)) ||
       (map->fillCells()->at(6) && map->fillCells()->at(7) && map->fillCells()->at(8)) ||
       (map->fillCells()->at(0) && map->fillCells()->at(4) && map->fillCells()->at(8)) ||
       (map->fillCells()->at(2) && map->fillCells()->at(4) && map->fillCells()->at(6)) ||
       (map->fillCells()->at(0) && map->fillCells()->at(3) && map->fillCells()->at(6)) ||
       (map->fillCells()->at(1) && map->fillCells()->at(4) && map->fillCells()->at(7)) ||
       (map->fillCells()->at(2) && map->fillCells()->at(5) && map->fillCells()->at(8)))
    {
        QMessageBox messageInfo;
        messageInfo.information(this, "Game Over", "You won!!!");
        ifGameOverValue = true;
        ifYouWantPlayAgain();
    }
    else
    if ((map->fillCellsComputer()->at(0) && map->fillCellsComputer()->at(1) && map->fillCellsComputer()->at(2)) ||
       (map->fillCellsComputer()->at(3) && map->fillCellsComputer()->at(4) && map->fillCellsComputer()->at(5)) ||
       (map->fillCellsComputer()->at(6) && map->fillCellsComputer()->at(7) && map->fillCellsComputer()->at(8)) ||
       (map->fillCellsComputer()->at(0) && map->fillCellsComputer()->at(4) && map->fillCellsComputer()->at(8)) ||
       (map->fillCellsComputer()->at(2) && map->fillCellsComputer()->at(4) && map->fillCellsComputer()->at(6)) ||
       (map->fillCellsComputer()->at(0) && map->fillCellsComputer()->at(3) && map->fillCellsComputer()->at(6)) ||
       (map->fillCellsComputer()->at(1) && map->fillCellsComputer()->at(4) && map->fillCellsComputer()->at(7)) ||
       (map->fillCellsComputer()->at(2) && map->fillCellsComputer()->at(5) && map->fillCellsComputer()->at(8)))
    {
        QMessageBox messageInfo;
        messageInfo.information(this, "Game Over", "You loose!!!");
        ifGameOverValue = true;
        ifYouWantPlayAgain();
    }
    else
    if (!map->countFreePlace())
    {
        QMessageBox messageInfo;
        messageInfo.information(this, "Game Over", "Draw!!!");
        ifGameOverValue = true;
        ifYouWantPlayAgain();
    }
}

void Widget::ifYouWantPlayAgain()
{
    QMessageBox messageQuestion;
    QMessageBox::StandardButton button;
    button = messageQuestion.question(this, "Continue?", "Do you want to play one more time?",
                                      QMessageBox::Yes | QMessageBox::No);

    if (button == QMessageBox::No)
        this->close();
    else
    {
        myMove = !myMove;
        ifGameOverValue = false;
        map->setFalseAfterGameOver();
        this->update();
        ifRestartGame = true;

        myChoosing = 0;
        mChooseX->setCheckable(false);
        mChooseO->setCheckable(false);
        this->setFixedSize(map->formSize() + 100, map->formSize());
    }
}

//set sum logic
bool Widget::computerDeffend()
{
    //1-level H
    if (map->fillCells()->at(0) && map->fillCells()->at(1) && !map->fillCells()->at(2) && !map->fillCellsComputer()->at(2))
    {
        map->setFilledCellComputer(2);
        return true;
    }else
    if (map->fillCells()->at(0) && !map->fillCells()->at(1) && map->fillCells()->at(2) && !map->fillCellsComputer()->at(1))
    {
        map->setFilledCellComputer(1);
        return true;
    }else
    if (!map->fillCells()->at(0) && map->fillCells()->at(1) && map->fillCells()->at(2) && !map->fillCellsComputer()->at(0))
    {
        map->setFilledCellComputer(0);
        return true;
    }else
    //2 level H
    if (map->fillCells()->at(3) && map->fillCells()->at(4) && !map->fillCells()->at(5) && !map->fillCellsComputer()->at(5))
    {
        map->setFilledCellComputer(5);
        return true;
    }else
    if (map->fillCells()->at(3) && !map->fillCells()->at(4) && map->fillCells()->at(5) && !map->fillCellsComputer()->at(4))
    {
        map->setFilledCellComputer(4);
        return true;
    }else
    if (!map->fillCells()->at(3) && map->fillCells()->at(4) && map->fillCells()->at(5) && !map->fillCellsComputer()->at(3))
    {
        map->setFilledCellComputer(3);
        return true;
    }else
    //3 level H
    if (map->fillCells()->at(6) && map->fillCells()->at(7) && !map->fillCells()->at(8) && !map->fillCellsComputer()->at(8))
    {
        map->setFilledCellComputer(8);
        return true;
    }else
    if (map->fillCells()->at(6) && !map->fillCells()->at(7) && map->fillCells()->at(8) && !map->fillCellsComputer()->at(7))
    {
        map->setFilledCellComputer(7);
        return true;
    }else
    if (!map->fillCells()->at(6) && map->fillCells()->at(7) && map->fillCells()->at(8) && !map->fillCellsComputer()->at(6))
    {
        map->setFilledCellComputer(6);
        return true;
    }else
    //1 level V
    if (map->fillCells()->at(0) && map->fillCells()->at(3) && !map->fillCells()->at(6) && !map->fillCellsComputer()->at(6))
    {
        map->setFilledCellComputer(6);
        return true;
    }else
    if (map->fillCells()->at(0) && !map->fillCells()->at(3) && map->fillCells()->at(6) && !map->fillCellsComputer()->at(3))
    {
        map->setFilledCellComputer(3);
        return true;
    }else
    if (!map->fillCells()->at(0) && map->fillCells()->at(3) && map->fillCells()->at(6) && !map->fillCellsComputer()->at(0))
    {
        map->setFilledCellComputer(0);
        return true;
    }else
    //2 level V
    if (map->fillCells()->at(1) && map->fillCells()->at(4) && !map->fillCells()->at(7) && !map->fillCellsComputer()->at(7))
    {
        map->setFilledCellComputer(7);
        return true;
    }else
    if (map->fillCells()->at(1) && !map->fillCells()->at(4) && map->fillCells()->at(7) && !map->fillCellsComputer()->at(4))
    {
        map->setFilledCellComputer(4);
        return true;
    }else
    if (!map->fillCells()->at(1) && map->fillCells()->at(4) && map->fillCells()->at(7) && !map->fillCellsComputer()->at(1))
    {
        map->setFilledCellComputer(1);
        return true;
    }else
    //3 level V
    if (map->fillCells()->at(2) && map->fillCells()->at(5) && !map->fillCells()->at(8) && !map->fillCellsComputer()->at(8))
    {
        map->setFilledCellComputer(8);
        return true;
    }else
    if (map->fillCells()->at(2) && !map->fillCells()->at(5) && map->fillCells()->at(8) && !map->fillCellsComputer()->at(5))
    {
        map->setFilledCellComputer(5);
        return true;
    }else
    if (!map->fillCells()->at(2) && map->fillCells()->at(5) && map->fillCells()->at(8) && !map->fillCellsComputer()->at(2))
    {
        map->setFilledCellComputer(2);
        return true;
    }else
    //1 diag
    if (map->fillCells()->at(0) && map->fillCells()->at(4) && !map->fillCells()->at(8) && !map->fillCellsComputer()->at(8))
    {
        map->setFilledCellComputer(8);
        return true;
    }else
    if (map->fillCells()->at(0) && !map->fillCells()->at(4) && map->fillCells()->at(8) && !map->fillCellsComputer()->at(4))
    {
        map->setFilledCellComputer(4);
        return true;
    }else
    if (!map->fillCells()->at(0) && map->fillCells()->at(4) && map->fillCells()->at(8) && !map->fillCellsComputer()->at(0))
    {
        map->setFilledCellComputer(0);
        return true;
    }else
    //2 diag
    if (map->fillCells()->at(2) && map->fillCells()->at(4) && !map->fillCells()->at(6) && !map->fillCellsComputer()->at(6))
    {
        map->setFilledCellComputer(6);
        return true;
    }else
    if (map->fillCells()->at(2) && !map->fillCells()->at(4) && map->fillCells()->at(6) && !map->fillCellsComputer()->at(4))
    {
        map->setFilledCellComputer(4);
        return true;
    }else
    if (!map->fillCells()->at(2) && map->fillCells()->at(4) && map->fillCells()->at(6) && !map->fillCellsComputer()->at(2))
    {
        map->setFilledCellComputer(2);
        return true;
    }

    return false;
}

bool Widget::computerAttack()
{
    //1-level H
    if (map->fillCellsComputer()->at(0) && map->fillCellsComputer()->at(1) && !map->fillCellsComputer()->at(2) && !map->fillCells()->at(2))
    {
        map->setFilledCellComputer(2);
        return true;
    }else
    if (map->fillCellsComputer()->at(0) && !map->fillCellsComputer()->at(1) && map->fillCellsComputer()->at(2) && !map->fillCells()->at(1))
    {
        map->setFilledCellComputer(1);
        return true;
    }else
    if (!map->fillCellsComputer()->at(0) && map->fillCellsComputer()->at(1) && map->fillCellsComputer()->at(2) && !map->fillCells()->at(0))
    {
        map->setFilledCellComputer(0);
        return true;
    }else
    //2 level H
    if (map->fillCellsComputer()->at(3) && map->fillCellsComputer()->at(4) && !map->fillCellsComputer()->at(5) && !map->fillCells()->at(5))
    {
        map->setFilledCellComputer(5);
        return true;
    }else
    if (map->fillCellsComputer()->at(3) && !map->fillCellsComputer()->at(4) && map->fillCellsComputer()->at(5) && !map->fillCells()->at(4))
    {
        map->setFilledCellComputer(4);
        return true;
    }else
    if (!map->fillCellsComputer()->at(3) && map->fillCellsComputer()->at(4) && map->fillCellsComputer()->at(5) && !map->fillCells()->at(3))
    {
        map->setFilledCellComputer(3);
        return true;
    }else
    //3 level H
    if (map->fillCellsComputer()->at(6) && map->fillCellsComputer()->at(7) && !map->fillCellsComputer()->at(8) && !map->fillCells()->at(8))
    {
        map->setFilledCellComputer(8);
        return true;
    }else
    if (map->fillCellsComputer()->at(6) && !map->fillCellsComputer()->at(7) && map->fillCellsComputer()->at(8) && !map->fillCells()->at(7))
    {
        map->setFilledCellComputer(7);
        return true;
    }else
    if (!map->fillCellsComputer()->at(6) && map->fillCellsComputer()->at(7) && map->fillCellsComputer()->at(8) && !map->fillCells()->at(6))
    {
        map->setFilledCellComputer(6);
        return true;
    }else
    //1 level V
    if (map->fillCellsComputer()->at(0) && map->fillCellsComputer()->at(3) && !map->fillCellsComputer()->at(6) && !map->fillCells()->at(6))
    {
        map->setFilledCellComputer(6);
        return true;
    }else
    if (map->fillCellsComputer()->at(0) && !map->fillCellsComputer()->at(3) && map->fillCellsComputer()->at(6) && !map->fillCells()->at(3))
    {
        map->setFilledCellComputer(3);
        return true;
    }else
    if (!map->fillCellsComputer()->at(0) && map->fillCellsComputer()->at(3) && map->fillCellsComputer()->at(6) && !map->fillCells()->at(0))
    {
        map->setFilledCellComputer(0);
        return true;
    }else
    //2 level V
    if (map->fillCellsComputer()->at(1) && map->fillCellsComputer()->at(4) && !map->fillCellsComputer()->at(7) && !map->fillCells()->at(7))
    {
        map->setFilledCellComputer(7);
        return true;
    }else
    if (map->fillCellsComputer()->at(1) && !map->fillCellsComputer()->at(4) && map->fillCellsComputer()->at(7) && !map->fillCells()->at(4))
    {
        map->setFilledCellComputer(4);
        return true;
    }else
    if (!map->fillCellsComputer()->at(1) && map->fillCellsComputer()->at(4) && map->fillCellsComputer()->at(7) && !map->fillCells()->at(1))
    {
        map->setFilledCellComputer(1);
        return true;
    }else
    //3 level V
    if (map->fillCellsComputer()->at(2) && map->fillCellsComputer()->at(5) && !map->fillCellsComputer()->at(8) && !map->fillCells()->at(8))
    {
        map->setFilledCellComputer(8);
        return true;
    }else
    if (map->fillCellsComputer()->at(2) && !map->fillCellsComputer()->at(5) && map->fillCellsComputer()->at(8) && !map->fillCells()->at(5))
    {
        map->setFilledCellComputer(5);
        return true;
    }else
    if (!map->fillCellsComputer()->at(2) && map->fillCellsComputer()->at(5) && map->fillCellsComputer()->at(8) && !map->fillCells()->at(2))
    {
        map->setFilledCellComputer(2);
        return true;
    }else
    //1 diag
    if (map->fillCellsComputer()->at(0) && map->fillCellsComputer()->at(4) && !map->fillCellsComputer()->at(8) && !map->fillCells()->at(8))
    {
        map->setFilledCellComputer(8);
        return true;
    }else
    if (map->fillCellsComputer()->at(0) && !map->fillCellsComputer()->at(4) && map->fillCellsComputer()->at(8) && !map->fillCells()->at(4))
    {
        map->setFilledCellComputer(4);
        return true;
    }else
    if (!map->fillCellsComputer()->at(0) && map->fillCellsComputer()->at(4) && map->fillCellsComputer()->at(8) && !map->fillCells()->at(0))
    {
        map->setFilledCellComputer(0);
        return true;
    }else
    //2 diag
    if (map->fillCellsComputer()->at(2) && map->fillCellsComputer()->at(4) && !map->fillCellsComputer()->at(6) && !map->fillCells()->at(6))
    {
        map->setFilledCellComputer(6);
        return true;
    }else
    if (map->fillCellsComputer()->at(2) && !map->fillCellsComputer()->at(4) && map->fillCellsComputer()->at(6) && !map->fillCells()->at(4))
    {
        map->setFilledCellComputer(4);
        return true;
    }else
    if (!map->fillCellsComputer()->at(2) && map->fillCellsComputer()->at(4) && map->fillCellsComputer()->at(6) && !map->fillCells()->at(2))
    {
        map->setFilledCellComputer(2);
        return true;
    }

    return false;
}

//radiobuttons
void Widget::chooseX()
{
    myChoosing = 1;

    this->setFixedSize(map->formSize(), map->formSize());

    if (!myMove)
    {
        if (map->countFreePlace())
        {
            computerTurn();
            if (!ifGameOverValue)
                ifGameOver();

            if (ifRestartGame)
            {
                ifRestartGame = false;
                return;
            }
        }
    }
}

void Widget::chooseO()
{
    myChoosing = 2;

    this->setFixedSize(map->formSize(), map->formSize());

    if (!myMove)
    {
        if (map->countFreePlace())
        {
            computerTurn();
            if (!ifGameOverValue)
                ifGameOver();

            if (ifRestartGame)
            {
                ifRestartGame = false;
                return;
            }
        }
    }
}
