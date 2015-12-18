#ifndef MULTICASTPARAMS_H
#define MULTICASTPARAMS_H

#include <QHostAddress>

class MulticastParams
{
public:
    MulticastParams();
    static QHostAddress getGroupAddress();
    static quint16 getGroupPort();
};

#endif // MULTICASTPARAMS_H
