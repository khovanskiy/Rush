#ifndef CONSOLE_H
#define CONSOLE_H

#include <QString>
#include <QVariant>
#include <QThread>
#include <QTextStream>

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

    static void printThreadId()
    {
        QTextStream cout(stdout);
        cout << "Current ID = " << QThread::currentThreadId() << "\n";
    }
};

#endif // CONSOLE_H
