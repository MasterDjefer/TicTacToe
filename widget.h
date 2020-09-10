#ifndef WIDGET_H
#define WIDGET_H
#include "map.h"
#include "geometry.h"
#include <QWidget>
#include <QPainter>
#include <QMouseEvent>
#include <QDebug>
#include <QMessageBox>
#include <QRadioButton>
#include <ctime>
#include <cstdlib>

class Widget : public QWidget
{
    Q_OBJECT

public:
    Widget();
    ~Widget();

private:
    Map *map;
    QRadioButton *mChooseX;
    QRadioButton *mChooseO;
    bool ifGameOverValue;
    bool ifRestartGame;
    bool myMove; //true-I false-computer
    int myChoosing;//1-X, 2-O 0-nothing

private:
    virtual void paintEvent(QPaintEvent *event);
    virtual void mousePressEvent(QMouseEvent *event);
    void computerTurn();
    void ifGameOver();
    void ifYouWantPlayAgain();
    bool computerDeffend();
    bool computerAttack();

private slots:
    void chooseX();
    void chooseO();
};

#endif // WIDGET_H
