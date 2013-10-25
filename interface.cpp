#include "interface.h"

Interface* Interface::instance = 0;

Interface::Interface()
{

}

Interface::~Interface()
{

}

Interface* Interface::gi()
{
    if (instance == 0)
    {
        instance = new Interface();
    }
    return instance;
}
