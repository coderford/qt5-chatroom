#ifndef CLIENTTCPSOCKET_H
#define CLIENTTCPSOCKET_H

#include <QObject>
#include <QTcpSocket>
#include <QDebug>

class ClientTcpSocket : public QObject
{
    Q_OBJECT
public:
    explicit ClientTcpSocket(QObject *parent = nullptr);
    void doConnect(QString host, quint16 port);

signals:

public slots:
    void connected();
    void disconnected();
    void bytesWritten(qint64 bytes);
    void readyRead();

private:
    QTcpSocket *socket;
};

#endif // CLIENTTCPSOCKET_H
