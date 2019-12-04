#include "serverhandler.h"

ServerHandler::ServerHandler(qintptr socketDescriptor, QObject *parent):
    QObject(parent)
{
    clientSocket = new QTcpSocket(parent);
    clientSocket->setSocketDescriptor(socketDescriptor);
    connect(clientSocket, &QTcpSocket::readyRead, this, &ServerHandler::clientReadData);
    connect(clientSocket, &QTcpSocket::disconnected, this, &ServerHandler::clientDisconnected);


    serverSocket = nullptr;

    ip = ServerIP::getNextConnection();
    if(!ip.port){
        clientSocket->close();
        this->deleteLater();
    }else{
        serverSocket = new QTcpSocket(parent);
        connect(serverSocket, &QTcpSocket::stateChanged, this, &ServerHandler::stateChanged);
        connect(serverSocket, &QTcpSocket::readyRead, this, &ServerHandler::serverReadData);
        connect(serverSocket, &QTcpSocket::disconnected, this, &ServerHandler::serverDisconnected);
        serverSocket->connectToHost(ip.addr, static_cast<quint16>(ip.port));
        connectionAttemps++;
    }
}

ServerHandler::~ServerHandler()
{
    delete clientSocket;
}

void ServerHandler::clientReadData()
{
    if(serverSocket->state() == QAbstractSocket::SocketState::ConnectedState){
        qDebug()<<"Receive data from Client ip "<<clientSocket->peerAddress()<<" port "<<clientSocket->peerPort();
        serverSocket->write(clientSocket->readAll());
        qDebug()<<"Proxy send to server ip "<<ip.addr<<" port "<<ip.port;
    }
}

void ServerHandler::serverReadData()
{
    qDebug()<<"Receive data from Server ip "<<serverSocket->peerAddress()<<" port "<<serverSocket->peerPort();
    clientSocket->write(serverSocket->readAll());
    qDebug()<<"Proxy send to client ip "<<clientSocket->peerAddress()<<" port "<<clientSocket->peerPort();
}

void ServerHandler::clientDisconnected()
{
    this->deleteLater();
}

void ServerHandler::serverDisconnected()
{

}

void ServerHandler::stateChanged(QAbstractSocket::SocketState socketState)
{
    qDebug()<<socketState;

    if(socketState == QAbstractSocket::SocketState::UnconnectedState){
        if(connectionAttemps ==  ServerIP::size()){
            clientSocket->close();
            this->deleteLater();
        }else{
            connectionAttemps++;
            ip = ServerIP::getNextConnection();
            serverSocket->connectToHost(ip.addr, static_cast<quint16>(ip.port));
        }
    }else if (socketState == QAbstractSocket::SocketState::ConnectedState){
        connectionAttemps = 0;
        clientReadData();
    }
}


