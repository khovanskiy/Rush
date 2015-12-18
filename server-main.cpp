#include "server.h"
#include <QApplication>

int main(int argc, char **argv) {
    Server server(argc, argv);
    return server.exec();
}
