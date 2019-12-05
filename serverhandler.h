#ifndef SERVERHANDLER_H
#define SERVERHANDLER_H

#include <QThread>
#include <QTcpSocket>
#include <serverip.h>

class ServerHandler: public QObject
{
    Q_OBJECT
    QTcpSocket *clientSocket;
    QTcpSocket *serverSocket;
    int connectionAttemps = 0;
    ServerIP::ServerAddress ip;

public:
    ServerHandler(qintptr socketDescriptor, QObject *parent = nullptr);
    ~ServerHandler() override;
private slots:
    void clientReadData();
    void serverReadData();
    void clientDisconnected();
    void serverDisconnected();

    void stateChanged(QAbstractSocket::SocketState socketState);

signals:
    void connectionUpdated(qintptr socketDescriptor, ServerIP::ServerAddress clientIp, ServerIP::ServerAddress serverIp);
    void connectionClosed(qintptr socketDescriptor);
};

#endif // SERVERHANDLER_H
