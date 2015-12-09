#ifndef LOADER_H
#define LOADER_H

#include "thread.h"
#include "common/eventdispatcher.h"

class Loader
{
public:
    Loader();
    void run();
};

#endif // LOADER_H
