#ifndef CLIENT_H
#define CLIENT_H

#include <QObject>
#include <QTcpSocket>
#include <QHostAddress>
#include "../dto/dtogenerator.h"
#include "../xml/xmlparser.h"
class Client : public QObject
{
    Q_OBJECT
public:
    Client(QObject* parent=nullptr);
    ~Client();
public:
    uint32_t getSuccessful(){return successfulPackets;}
    uint32_t getAllPackets(){return allPackets;}
    uint32_t getErrorNumber(){return errorCnt;}
signals:
    void connected();
    //void fileSent();
    void error(const QString& errorMessage);

private slots:
    void socketError(const QString& errorMessage); //not used
    void updateErrorCnt();
public slots:
    void setFileName(const QString& fileName);
    void generateFile();

    void setServPort(const quint16& port);
    void setServAddr(const QHostAddress& addr);
    void connectToServer();
    void disconnectFromServer();
    void clientSendData();
    void connectionClosed();
private:
    QString fileName;
    uint32_t successfulPackets;
    uint32_t allPackets;
    uint32_t errorCnt;

    QHostAddress addr;
    quint16 port;
    QTcpSocket* sock;
    XMLParser par;

};

#endif // CLIENT_H
