#include "clienttcpsocket.h"

ClientTcpSocket::ClientTcpSocket(QObject *parent) : QObject(parent)
{
}

void ClientTcpSocket::doConnect(QString host, quint16 port)
{
    socket = new QTcpSocket(this);

    connect(socket, SIGNAL(connected()), this, SLOT(connected()));
    connect(socket, SIGNAL(disconnected()), this, SLOT(disconnected()));
    connect(socket, SIGNAL(bytesWritten(qint64)), this, SLOT(bytesWritten(qint64));
    connect(socket, SIGNAL(readyRead()), this, SLOT(readyRead()));

    socket->connectToHost(host, port);
    if(!socket->waitForBytesWritten(5000)) {
        qDebug() << "ERROR: " << socket->errorString();
    }
}
