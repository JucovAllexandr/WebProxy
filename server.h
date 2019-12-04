#ifndef SERVER_H
#define SERVER_H

#include <QTcpServer>
#include <serverhandler.h>

class Server: public QTcpServer
{
public:
    Server(QObject *parent = nullptr);
protected:
    void incomingConnection(qintptr socketDescriptor) override;
};

#endif // SERVER_H
