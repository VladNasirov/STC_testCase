#include "server.h"

server::server(QObject *parent):QObject(parent), serv(new QTcpServer(this)), errorCnt(0)
{
#ifdef DEBUG_LOG
    qDebug()<<"Server thread "<<QThread::currentThreadId()<<" running...";
#endif
    connect(serv, &QTcpServer::newConnection, this, &server::onNewConnection);

}

server::~server()
{
    delete thr;
    delete serv;
}

bool server::startServer()
{
#ifdef DEBUG_LOG
    qDebug()<<"Starting server on port"<<port;
#endif
    if(!serv->isListening())
    {
       serv->listen(QHostAddress::Any, port);
    }
    else
    {
       errorCnt++;
       emit error("Server is already listening");
       return false;
    }
    return true;
}

void server::stop()
{
#ifdef DEBUG_LOG
    qDebug()<<"Stoping server... ";
#endif
    QList<QTcpSocket*> clients=serv->findChildren<QTcpSocket*>();
    for(QTcpSocket* client: clients)
    {
        client->disconnectFromHost();
    }
    disconnect(serv, &QTcpServer::newConnection, this, &server::onNewConnection);
    serv->close();
}

void server::setAddr(const QHostAddress &addr)
{
    this->addr=addr;
}

void server::setPort(const quint16 &port)
{
    this->port=port;
}

void server::setFileName(const QString &fileName)
{
    this->fileName=fileName;
}

void server::readFile()
{
    mtx.lock();
    thr=new XMLThread(this);
    connect(this, &server::error, thr, &XMLThread::error);
    thr->setFile(fileName);
    thr->start();
    mtx.unlock();
}

void server::onNewConnection()
{
    QTcpSocket* sock=serv->nextPendingConnection();
    qDebug()<<"We got new connection!";
    connect(sock, &QTcpSocket::readyRead, this, &server::readData);
    connect(sock, &QTcpSocket::disconnected, this, &server::clientDisconnected);
    //sock->setParent(this);
}

void server::readData()
{
    QTcpSocket* sock= qobject_cast<QTcpSocket*>(sender());
    if(!sock)
    {
        return;
    }
#ifdef DEBUG_LOG
    qDebug()<<"Client sock addr is:"<<sock->peerAddress()<<":"<<sock->peerPort();
#endif
    QByteArray data;
    while(sock->bytesAvailable()>0)
    {
        data=sock->readAll();
    }
#ifdef DEBUG_LOG
    qDebug()<<"Recieved data:"<<data;
#endif
    mtx.lock();
    packets++;
    QFile file(fileName);
    if(!file.open(QIODevice::WriteOnly | QIODevice::Text))
    {
        errorCnt++;
        emit error("Failed to safe XML file "+fileName);
    }

    file.write(data);
    file.close();
    mtx.unlock();
    emit fileRecv();
    readFile();
}

void server::clientDisconnected()
{
    QTcpSocket* sock= qobject_cast<QTcpSocket*>(sender());
    if(sock)
    {
        sock->deleteLater();
    }
}
