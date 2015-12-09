#include "program.h"

#include <QApplication>
#include "graphiccore.h"

int main(int argc, char** argv)
{
    QStringList paths = QCoreApplication::libraryPaths();
    paths.append(".");
    paths.append("platforms");
    QCoreApplication::setLibraryPaths(paths);

    QApplication a(argc, argv);
    GraphicCore window;
    window.show();
    return a.exec();
}
