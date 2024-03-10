#ifndef SERVER_H
#define SERVER_H

#include <QTcpServer>
#include <QTcpSocket>
#include <QObject>
#include "xmlthread.h"
#include <QMutex>
#include <QList>
class server :public QObject
{
    Q_OBJECT
public:
    server(QObject* parent=nullptr);
    ~server();
    void setAddr(const QHostAddress& addr);
    void setPort(const quint16& port);
    void setFileName(const QString& fileName);
    void readFile();
    uint32_t getErrorCnt(){return errorCnt;}
    uint32_t getPacketsNumber(){return packets;}
signals:
    void fileRecv();
    void error(const QString& errorMessage);
private slots:
    void onNewConnection();
    void readData();
    void clientDisconnected();
public slots:
    bool startServer();
    void stop();
private:
    QString fileName;
    uint32_t errorCnt;
    uint32_t packets;
    QHostAddress addr;
    quint16 port;
    QTcpServer* serv;
    QMutex mtx;
    XMLThread* thr;
};

#endif // SERVER_H
