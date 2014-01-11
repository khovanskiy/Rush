#include "exitstate.h"

#include "graphiccore.h"

ExitState::ExitState()
{

}

void ExitState::init()
{
    GraphicCore::gi()->close();
}
