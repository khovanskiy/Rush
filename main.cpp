#include "program.h"

#include <QApplication>
#include "graphiccore.h"

int main(int argc, char* argv)
{
    QApplication a(argc, &argv);
    GraphicCore window;
    window.show();
    return a.exec();
}
