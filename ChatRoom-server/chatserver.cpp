#include "chatserver.h"

ChatServer::ChatServer(QObject *parent) : QTcpServer(parent)
{
}

void ChatServer::start()
{
    if(!this->listen(QHostAddress::Any, this->port)) {
        qDebug() << "Could not start server!";
    } else {
        qDebug() << "Server ready and listening on port" << this->port;
    }
}

void ChatServer::incomingConnection(qintptr handle)
{
    // create new thread to handle client
    ClientHandlerThread *thread = new ClientHandlerThread(handle, this);
    handlers[handle] = thread;

    // connect signals and slots
    connect(thread, SIGNAL(finished(long long)), this, SLOT(on_threadFinished(long long)));
    connect(thread, SIGNAL(messageFromClient(long long, QByteArray)),
            this, SLOT(on_messageFromClient(long long, QByteArray)));
    connect(this, SIGNAL(messageToAll(QByteArray)), thread, SLOT(on_messageToAll(QByteArray)));

    thread->start();
}

void ChatServer::on_messageFromClient(long long threadId, QByteArray data)
{
    QString toSend = "[" + handlers[threadId]->getNickname() + "] ";
    toSend += QString::fromStdString(data.toStdString());
    emit messageToAll(toSend.toUtf8());
}

void ChatServer::on_threadFinished(long long threadId)
{
    QString disconnectMessage = "\n** " + handlers[threadId]->getNickname() + " has left the chat **\n";
    handlers.remove(threadId);

    emit messageToAll(disconnectMessage.toUtf8());
}
