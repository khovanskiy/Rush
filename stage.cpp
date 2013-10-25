#include "stage.h"

Stage* Stage::instance = 0;

Stage::Stage()
{

}

Stage::~Stage()
{

}

Stage* Stage::getInstance()
{
    if (instance == 0)
    {
        instance = new Stage();
    }
    return instance;
}
