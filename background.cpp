#include "background.h"

Background* Background::instance = 0;

Background::Background()
{

}

Background::~Background()
{

}

Background* Background::getInstance()
{
    if (instance == 0)
    {
        instance = new Background();
    }
    return instance;
}
