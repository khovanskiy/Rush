#include "gameviewobject.h"
#include <QCoreApplication>
#include "console.h"

GameViewObject::GameViewObject()
{
    m_to_px = 1;
    valid = true;
}

GameViewObject::~GameViewObject()
{

}

bool GameViewObject::isValid()
{
    return valid;
}

void GameViewObject::invalidate()
{
    valid = false;
}
