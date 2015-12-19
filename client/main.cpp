#include "program.h"

#include <QApplication>
#include <iostream>
#include <common/Arguments.h>
#include "graphiccore.h"

int main(int argc, char** argv)
{
    std::cout << "Arguments:" << std::endl;
    for (int i = 0; i < argc; ++i) {
        std::cout << argv[i] << std::endl;
    }
    if (argc > 1) {
        Arguments::gi()->setHostname(argv[1]);
    }
    QStringList paths = QCoreApplication::libraryPaths();
    paths.append(".");
    paths.append("platforms");
    QCoreApplication::setLibraryPaths(paths);

    QApplication a(argc, argv);
    GraphicCore window;
    window.show();
    return a.exec();
}
