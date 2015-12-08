#include "idsystem.h"

IDSystem::IDSystem()
{
    next_id = 1;
}

void IDSystem::release(int id)
{

}

int IDSystem::next()
{
    int id = next_id;
    ++next_id;
    return id;
}
