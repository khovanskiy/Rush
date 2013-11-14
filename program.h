#ifndef PROGRAM_H
#define PROGRAM_H

#include <QMainWindow>

#include "game.h"

class Program : public QMainWindow
{
    Q_OBJECT
    
public:
    Program(QWidget *parent = 0);
    ~Program();
private:
    Game* game;
};

#endif // PROGRAM_H
