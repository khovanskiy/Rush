#ifndef PROGRAM_H
#define PROGRAM_H

#include <QMainWindow>

class Program : public QMainWindow
{
    Q_OBJECT
    
public:
    Program(QWidget *parent = 0);
    ~Program();
};

#endif // PROGRAM_H
