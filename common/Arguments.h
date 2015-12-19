//
// Created by victor on 19.12.15.
//

#ifndef CLIENT_ARGUMENTS_H
#define CLIENT_ARGUMENTS_H

#include <QString>

class Arguments {
public:
    static Arguments* gi();
    Arguments() {
        hostname = "127.0.0.1";
    }
    QString getHostname() {
        return hostname;
    }
    void setHostname(QString hostname) {
        this->hostname = hostname;
    }
private:
    static Arguments* instance;
    QString hostname;
};

#endif //CLIENT_ARGUMENTS_H
