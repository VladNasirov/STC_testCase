#include "client.h"

Client::Client(QObject *parent): QObject(parent), sock(new QTcpSocket(this)), par(this), allPackets(0), successfulPackets(0), errorCnt(0)
{
    connect(sock, &QTcpSocket::connected, this, &Client::connected);
    //connect(sock, &QTcpSocket::bytesWritten, this,  &Client::fileSent);
    connect(this, &Client::error, this, &Client::socketError);
    connect(sock, &QTcpSocket::disconnected, this, &Client::connectionClosed);
    connect(&par, &XMLParser::parseError, this, &Client::error);
    connect(this, &Client::error, this, &Client::updateErrorCnt);
}

Client::~Client()
{
    delete sock;
}


void Client::connectToServer()
{
    sock->connectToHost(addr, port);
    qDebug()<<"connected to"<<addr<<":"<<port;
}

void Client::disconnectFromServer()
{
    if(sock->state()==QAbstractSocket::ConnectedState)
    {
        sock->disconnectFromHost();
    }
}

void Client::socketError(const QString& errorMessage)
{
    qWarning()<<errorMessage;
}

//For QLabel view
void Client::updateErrorCnt()
{
    errorCnt++;
}

void Client::setFileName(const QString &fileName)
{
    this->fileName=fileName;
}

void Client::clientSendData()
{
    QFile file(fileName);
    if(!file.open(QIODevice::ReadOnly))
    {
        emit error("Can`t open file!");
        return;
    }
    QByteArray data=file.readAll();
    file.close();

    qint64 bytesWritten=sock->write(data);
    if(bytesWritten==-1)
    {
        emit error("Data send failed!");
        allPackets++;
    }
    else
    {
        successfulPackets++;
        allPackets++;
        qDebug()<<"Data send!!";
    }
}

void Client::setServPort(const quint16 &port)
{
    this->port=port;
}

void Client::setServAddr(const QHostAddress &addr)
{
    this->addr=addr;
}

void Client::connectionClosed()
{
    qDebug()<<"Connection closed";
}
//Random DTO_struct generated, then parsed to XML file
void Client::generateFile()
{
    DTOGenerator gen;
    DTO_struct str=gen.generateStruct();
    par.generateXML(fileName, str);
#ifdef DEBUG_LOG
    printDTO(str);
#endif
    str.key_value_params.clear();
}
