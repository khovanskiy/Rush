#include "protocol.h"

Protocol::Protocol()
{

}

QString Protocol::nextString()
{
    QString result = QVariant(list.front()).toString();
    list.pop_front();
    return result;
}

void Protocol::putString(const QString& value)
{
    list.push_back(value);
}

double Protocol::nextDouble()
{
    double result = QVariant(list.front()).toDouble();
    list.pop_front();
    return result;
}

int Protocol::nextInt()
{
    int result = QVariant(list.front()).toInt();
    list.pop_front();
    return result;
}

void Protocol::putDouble(double value)
{
    list.push_back(QVariant(value).toString());
}

void Protocol::putInt(int value)
{
    list.push_back(QVariant(value).toString());
}

void Protocol::clear()
{
    list.clear();
}

const QByteArray& Protocol::toByteArray()
{
    buffer.clear();
    for (int i = 0; i < list.size() - 1; ++i)
    {
        buffer.append(list[i]);
        buffer.append(";");
    }
    buffer.append(list[list.size() - 1]);
    buffer.append("\n");
    return buffer;
}
