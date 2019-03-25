#include "customtcpsocket.h"

CustomTcpSocket::CustomTcpSocket(QObject *parent) : QTcpSocket(parent)
{

}

void CustomTcpSocket::on_messageToSocket(QByteArray data)
{
    write(data);
}
