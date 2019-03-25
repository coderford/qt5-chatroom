#include "clienthandlerthread.h"

ClientHandlerThread::ClientHandlerThread(qintptr handle, QObject *parent)
    : QThread(parent)
{
    this->id = handle;
}

void ClientHandlerThread::run()
{
    // create and configure new socket
    socket = new CustomTcpSocket();

    if(!socket->setSocketDescriptor(id)) {
        emit error(socket->error());
        exit(1);
    }
    qDebug() << "[" << id << "] connected";

    // connect signals and slots
    connect(socket, SIGNAL(readyRead()), this, SLOT(readyRead()), Qt::DirectConnection);
    connect(socket, SIGNAL(disconnected()), this, SLOT(disconnected()));
    connect(this, SIGNAL(messageToSocket(QByteArray)), socket, SLOT(on_messageToSocket(QByteArray)));

    // start execution loop
    exec();
}

void ClientHandlerThread::readyRead()
{
    // read all data and emit a signal to alert main thread
    QByteArray data = socket->readAll();

    // the first transmission from a client will be his nickname
    if(!nicknameReceived) {
        nickname = QString::fromStdString(data.toStdString());
        nicknameReceived = true;
    }
    else emit messageFromClient(id, data);
}

void ClientHandlerThread::disconnected()
{
    // schedule socket for deletion and terminate this thread
    socket->deleteLater();
    qDebug() << "[" << id << "] disconnected";
    emit finished(id);
    exit(0);
}

QHostAddress ClientHandlerThread::getPeerAddress()
{
    return socket->peerAddress();
}

void ClientHandlerThread::on_messageToAll(QByteArray data)
{
    emit messageToSocket(data);
}

QString ClientHandlerThread::getNickname()
{
    return nickname;
}

void ClientHandlerThread::setNickname(QString newName)
{
    nickname = newName;
}
