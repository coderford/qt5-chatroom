#ifndef CHATSERVER_H
#define CHATSERVER_H

#include <QTcpServer>
#include <QHostAddress>
#include "clienthandlerthread.h"
#include <QDebug>

#include <QMap>

class ChatServer : public QTcpServer
{
    Q_OBJECT
public:
    explicit ChatServer(QObject *parent = nullptr);
    void start();

signals:
    void messageToAll(QByteArray data);

public slots:
    void on_messageFromClient(long long threadId, QByteArray data);
    void on_threadFinished(long long threadId);

protected:
    void incomingConnection(qintptr handle);

private:
    quint16 port = 1729;
    QMap<qintptr, ClientHandlerThread *> handlers;

    void sendToAllThreads(QString toSend);
};

#endif // CHATSERVER_H
