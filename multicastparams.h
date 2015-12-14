#ifndef MULTICASTPARAMS_H
#define MULTICASTPARAMS_H

#include <QHostAddress>

class MulticastParams
{
public:
    MulticastParams();
    static QHostAddress getGroupAddress();
    static int getGroupPort();
};

#endif // MULTICASTPARAMS_H
