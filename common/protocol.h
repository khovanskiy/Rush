#ifndef PROTOCOL_H
#define PROTOCOL_H

#include <QString>
#include <QVariant>
#include <deque>

#define AUTH 1
#define LOGIN 2
#define LOGOUT 4
#define ADD_OBJECT 8
#define REMOVE_OBJECT 16
#define UPDATE_OBJECT 32
#define PLAYER_IO 32
#define PLAYER_STAT 64

class Protocol
{
public:
    Protocol();
    void putString(const QString& value);
    QString nextString();
    void putInt(int value);
    void putDouble(double value);
    int nextInt();
    double nextDouble();
    void clear();
    const QByteArray& toByteArray();
private:
    std::deque<QString> list;
    QByteArray buffer;
};

#endif // PROTOCOL_H
