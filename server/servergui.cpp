#include "servergui.h"

serverGUI::serverGUI(QWidget *parent)
    : QWidget{parent}
{
    serv=new server(this);
    QVBoxLayout* lay= new QVBoxLayout(this);

    QPushButton* start_button = new QPushButton("Start the server", this);
    connect(start_button, &QPushButton::clicked, serv, &server::startServer);

    QPushButton* stop_button = new QPushButton("Stop the server", this);
    connect(stop_button, &QPushButton::clicked, serv, &server::stop);

    QLabel* error_label = new QLabel("Errors: 0", this);
    connect(serv, &server::error, this, &serverGUI::updateError);

    QTextEdit* text_ip = new QTextEdit("127.0.0.1", this);
    QTextEdit* port=new QTextEdit("2020", this);
    QTextEdit* fileName_text = new QTextEdit("file.xml", this);

    QPushButton* applyText_button = new QPushButton("Apply", this);
    connect(applyText_button, &QPushButton::clicked, this, &serverGUI::setAddrandPort);
    connect(applyText_button, &QPushButton::clicked, this, &serverGUI::setFile);

    QLabel* packetNumber = new QLabel("Successfuly recv packets = ", this);
    connect(serv, &server::fileRecv, this, &serverGUI::updatePackets);


    lay->addWidget(start_button);
    lay->addWidget(stop_button);
    lay->addWidget(error_label);
    lay->addWidget(text_ip);
    lay->addWidget(port);
    lay->addWidget(fileName_text);
    lay->addWidget(applyText_button);
    lay->addWidget(packetNumber);

    this->setLayout(lay);
}

void serverGUI::setAddrandPort()
{
    QLayoutItem* item=this->layout()->itemAt(3);
    if(item &&item->widget())
    {
        QTextEdit* text_ip=qobject_cast<QTextEdit*>(item->widget());
        if(text_ip)
        {
#ifdef DEBUG_LOG
            qDebug()<<text_ip->toPlainText();
#endif
            serv->setAddr(QHostAddress(text_ip->toPlainText()));
        }
    }
    item=this->layout()->itemAt(4);
    if(item &&item->widget())
    {
        QTextEdit* port=qobject_cast<QTextEdit*>(item->widget());
        if(port)
        {
#ifdef DEBUG_LOG
            qDebug()<<port->toPlainText();
#endif
            serv->setPort(quint16(port->toPlainText().toUShort()));
        }
    }
}

void serverGUI::setFile()
{
    QLayoutItem* item=this->layout()->itemAt(5);
    if(item &&item->widget())
    {
        QTextEdit* fileName=qobject_cast<QTextEdit*>(item->widget());
        if(fileName)
        {
#ifdef DEBUG_LOG
            qDebug()<<"FILENAME="<<fileName->toPlainText();
#endif
            serv->setFileName(fileName->toPlainText());
        }
    }
}

void serverGUI::updateError(const QString &error)
{
#ifdef DEBUG_LOG
    qDebug()<<error;
#endif
    QLayoutItem* item=this->layout()->itemAt(2);
    if(item &&item->widget())
    {
        QLabel* errorLab=qobject_cast<QLabel*>(item->widget());
        if(errorLab)
        {
            QString str("Errors: "+QString::number(serv->getErrorCnt()));
            errorLab->setText(str);
        }
    }
}

void serverGUI::updatePackets()
{
    QLayoutItem* item=this->layout()->itemAt(7);
    if(item &&item->widget())
    {
        QLabel* packetLab=qobject_cast<QLabel*>(item->widget());
        if(packetLab)
        {
            QString str("Successfuly recved packets = ["+QString::number(serv->getPacketsNumber())+"]");
            packetLab->setText(str);
        }
    }
}

