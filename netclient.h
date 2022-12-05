#ifndef NETCLIENT_H
#define NETCLIENT_H

#include <QObject>
#include <QUdpSocket>
#include <QNetworkDatagram>

class netClient : public QObject
{
    Q_OBJECT
public:
    explicit netClient(QObject *parent = nullptr, QString HostAddr = "127.0.0.1");

signals:

public slots:
    bool writeDatagram(QByteArray data);

private:
    QUdpSocket *socket;
    QHostAddress *HostIP;
};

#endif // NETCLIENT_H
