#ifndef PROGRAM_H
#define PROGRAM_H

#include <QMainWindow>

#include "graphiccore.h"
#include "game.h"

class Program : public QMainWindow
{
    Q_OBJECT
    
public:
    Program(QWidget *parent = 0);
    ~Program();
private:
    GraphicCore *core;
    Game* game;
    QTimer* ticks_timer;
private slots:
    void onTick();
};

#endif // PROGRAM_H
