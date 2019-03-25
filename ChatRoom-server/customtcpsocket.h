#ifndef CUSTOMTCPSOCKET_H
#define CUSTOMTCPSOCKET_H

#include <QTcpSocket>

class CustomTcpSocket : public QTcpSocket
{
    Q_OBJECT
public:
    CustomTcpSocket(QObject *parent = nullptr);

public slots:
    void on_messageToSocket(QByteArray data);
};

#endif // CUSTOMTCPSOCKET_H
