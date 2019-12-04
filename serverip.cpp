#include "serverip.h"

QVector<ServerIP::ServerAddress> ServerIP::connections;
int ServerIP::nextConn = 0;

void ServerIP::pushConnection(QString address, int port)
{
    connections.push_back(ServerAddress(address, port));
}

ServerIP::ServerAddress ServerIP::getNextConnection()
{
    ServerAddress adr;
    if(!connections.isEmpty()){
        adr = connections.at(nextConn);
        nextConn++;
        if(nextConn > connections.size() - 1){
            nextConn = 0;
        }
    }
    return  adr;
}

int ServerIP::size()
{
    return connections.size();
}
