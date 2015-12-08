#include "iostream"

#include <QApplication>

#include "vector2d.h"
#include "console.h"
#include "server.h"

int main(int argc, char** argv)
{
    QApplication a(argc, argv);
    Server w;
    w.show();
    return a.exec();
}
