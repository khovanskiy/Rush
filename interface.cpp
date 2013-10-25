#include "interface.h"

Interface* Interface::instance = 0;

Interface::Interface()
{

}

Interface::~Interface()
{

}

Interface* Interface::getInstance()
{
    if (instance == 0)
    {
        instance = new Interface();
    }
    return instance;
}
