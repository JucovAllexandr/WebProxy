#ifndef SERVERIP_H
#define SERVERIP_H

#include <QHostAddress>
class ServerIP
{
public:
    struct ServerAddress{
        QHostAddress addr;
        int port;
        ServerAddress(){
            port = 0;
        }
        ServerAddress(QString address, int port){
            this->port = port;
            addr.setAddress(address);
        }
    };

private:
    static QVector<ServerAddress> connections;
    static int nextConn;

public:
    static void pushConnection(QString address, int port);
    static ServerAddress getNextConnection();
    static int size();
};

#endif // SERVERIP_H
