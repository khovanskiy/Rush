#ifndef API_H
#define API_H

#include <QObject>
#include <QByteArray>
#include <QNetworkAccessManager>
#include <QNetworkRequest>
#include <QNetworkReply>
#include <QJsonDocument>
#include <QJsonObject>
#include <QJsonArray>

#include "console.h"

class API : public QObject
{
    Q_OBJECT
public:
    virtual ~API();

    void request(const QString& act, const QVariantMap& params);

    static API& gi()
    {
        static API api;
        return api;
    }

private slots:
    void onResult(QNetworkReply*);

private:
    API();
    QNetworkAccessManager* networkManager;
};

#endif // API_H
