#include "netclient.h"
#include "mainwindow.h"
#include <QHostAddress>

netClient::netClient(QObject *parent, QString HostAddr) : QObject(parent)
{
    socket = new QUdpSocket(this);
    HostIP = new QHostAddress(HostAddr);

}

bool netClient::writeDatagram(QByteArray data)
{
    socket->writeDatagram(data.data(), data.size(), *HostIP, 45454);
    socket->waitForBytesWritten(5000);
}



