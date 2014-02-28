#ifndef SERVER_H
#define SERVER_H

#include <QObject>
#include <QMainWindow>
#include <QtNetwork/QNetworkAccessManager>
#include <QtNetwork/QNetworkReply>

#include "console.h"

class Server : public QMainWindow
{
    Q_OBJECT
public:
    Server();
    virtual ~Server();
public slots:
    void onResult(QNetworkReply* reply);
private:
    QNetworkAccessManager* networkManager;
};

#endif // SERVER_H
