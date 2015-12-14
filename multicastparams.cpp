#include "multicastparams.h"

MulticastParams::MulticastParams()
{

}

QHostAddress MulticastParams::getGroupAddress()
{
    return QHostAddress("239.255.43.21");
}

int MulticastParams::getGroupPort()
{
    return 45454;
}

