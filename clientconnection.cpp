#include "clientconnection.h"
#include <QString>

ClientConnection::ClientConnection(QObject *parent=0):QObject(parent)
{
    socket = new QTcpSocket(this);
    connect(socket, SIGNAL(connected()), this, SLOT(conectado()));
    connect(socket, SIGNAL(readyRead()), this, SLOT(recibirData()));
    connect(socket, SIGNAL(disconnected()), this, SLOT(desconectado()));
    connect(socket, SIGNAL(error(QAbstractSocket::SocketError)), this, SLOT(displayError(QAbstractSocket::SocketError)));
    user = "";
    pass = "";
    dataSize = 0;
    estaConectado = false;
    arrayData.clear();
}

void ClientConnection::recibirData(){
    if(dataSize == 0){
        QDataStream stream(socket);
        stream.setVersion(QDataStream::Qt_5_0);
        if(socket->bytesAvailable() < sizeof(quint32))
            return;
         stream >> dataSize;
         qDebug() << "DataSize: " << dataSize;
    }
    if(socket->bytesAvailable() < dataSize){
        qDebug() << "Bytes Available:" << socket->bytesAvailable() << "DataSize:" << dataSize;
        qDebug() << "Not enough data";
        return;
    }
    QByteArray arr = socket->read(dataSize);
    parseMessage(arr);
    dataSize = 0;
}

void ClientConnection::parseMessage(QByteArray){

}

void ClientConnection::conectado(){
    estaConectado = true;
    emit signalConectado();
}

void ClientConnection::desconectado(){
    estaConectado = false;
    socket->close();

    user = "";
    pass = "";
    dataSize = 0;
    estaConectado = false;
    arrayData.clear();

    emit signalDesconectado();
}

void ClientConnection::displayError(QAbstractSocket::SocketError sError){
    switch(sError){
    case QAbstractSocket::RemoteHostClosedError:
        break;
    case QAbstractSocket::HostNotFoundError:
        emit connectionError("Client", "Host not found");
        break;
    case QAbstractSocket::ConnectionRefusedError:
        emit connectionError("Client", "Connection Refused");
        break;
    default:
        emit connectionError("Client", tr("Error ocurred: %1").arg(socket->errorString()));
    }
}

void ClientConnection::desconectar(){
    socket->disconnectFromHost();
}

void ClientConnection::sendMessage(QString msg){
    if(socket->isValid())
        socket->write(msg.toLatin1());
}

void ClientConnection::conectar(QString host, int port){
    socket->abort();
    socket->connectToHost(host, port);
}
