#ifndef SERVER_H
#define SERVER_H

#include <QTcpServer>
#include <serverhandler.h>

class Server: public QTcpServer
{
    Q_OBJECT
public:
    Server(QObject *parent = nullptr);
protected:
    void incomingConnection(qintptr socketDescriptor) override;

signals:
    void connectionUpdated(qintptr socketDescriptor, ServerIP::ServerAddress clientIp, ServerIP::ServerAddress serverIp);
    void connectionClosed(qintptr socketDescriptor);

};

#endif // SERVER_H
