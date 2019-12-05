#include "server.h"

Server::Server(QObject *parent):
    QTcpServer(parent)
{

}

void Server::incomingConnection(qintptr socketDescriptor)
{
   ServerHandler *handler = new ServerHandler(socketDescriptor, this);
   connect(handler, &ServerHandler::connectionUpdated, this, [this](qintptr socketDescriptor, ServerIP::ServerAddress clientIp, ServerIP::ServerAddress serverIp){
       emit connectionUpdated(socketDescriptor, clientIp, serverIp);
   });

   connect(handler, &ServerHandler::connectionClosed, this, [this](qintptr socketDescriptor){
       emit connectionClosed(socketDescriptor);
   });
}
