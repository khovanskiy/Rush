#ifndef CONSOLE_H
#define CONSOLE_H

#include <QString>
#include <QVariant>
#include <QThread>
#include <QTextStream>

#include "vector2d.h"
#include "matrix.h"

class Console
{
public:
    template<class T>
    static void print(T something)
    {
        QTextStream cout(stdout);
        cout << something << "\n";
    }

    static void print(QString string)
    {
        print<QString>(string);
    }

    static void print(Vector2D v)
    {
        print(QString("(")+QVariant(v.x).toString()+","+QVariant(v.y).toString()+")");
    }

    static void print(QMatrix m)
    {
        QString temp = "[";
        temp += QVariant(m.m11()).toString() + ",";
        temp += QVariant(m.m12()).toString() + ",0,";
        temp += QVariant(m.m21()).toString() + ",";
        temp += QVariant(m.m22()).toString() + ",0,";
        temp += QVariant(m.dx()).toString() + ",";
        temp += QVariant(m.dy()).toString() + ",1]";
        print(temp);
    }

    static void print(Matrix m)
    {
        QString temp = "[";
        temp += QVariant(m.M11).toString() + ",";
        temp += QVariant(m.M12).toString() + ",0,";
        temp += QVariant(m.M21).toString() + ",";
        temp += QVariant(m.M22).toString() + ",0,";
        temp += QVariant(m.M31).toString() + ",";
        temp += QVariant(m.M32).toString() + ",1]";
        print(temp);
    }

    static void printThreadId()
    {
        QTextStream cout(stdout);
        cout << "Current ID = " << QThread::currentThreadId() << "\n";
    }
};

#endif // CONSOLE_H
