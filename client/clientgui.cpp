#include "clientgui.h"

clientGUI::clientGUI(QWidget *parent)
    : QWidget{parent}
{
    cli=new Client(this);
    QVBoxLayout* lay= new QVBoxLayout(this);

    QPushButton* connect_button = new QPushButton("Connect to Server", this);
    connect(connect_button, &QPushButton::clicked, cli, &Client::connectToServer);
    QPushButton* disconnect_button = new QPushButton("Disconnect from Server", this);
    connect(disconnect_button, &QPushButton::clicked, cli, &Client::disconnectFromServer);

    QPushButton* generateXML_button = new QPushButton("Generate XML", this);
    connect(generateXML_button, &QPushButton::clicked, cli, &Client::generateFile);

    QPushButton* send_button= new QPushButton("Send data", this);
    connect(send_button, &QPushButton::clicked, cli, &Client::clientSendData);

    QLabel* error_label = new QLabel("Errors: 0", this);
    connect(cli, &Client::error, this, &clientGUI::updateError);

    QTextEdit* text_ip = new QTextEdit("127.0.0.1", this);
    QTextEdit* port=new QTextEdit("2020", this);
    QTextEdit* fileName_text = new QTextEdit("file.xml", this);

    QPushButton* applyText = new QPushButton("Apply", this);
    connect(applyText, &QPushButton::clicked, this, &clientGUI::setAddrandPort);
    connect(applyText, &QPushButton::clicked, this, &clientGUI::setFile);

    QLabel* packetNumber = new QLabel("Successfuly sent packets = ", this);
    connect(send_button, &QPushButton::clicked, this, &clientGUI::updatePackets);

    lay->addWidget(connect_button); //0
    lay->addWidget(disconnect_button); //1
    lay->addWidget(generateXML_button); //2
    lay->addWidget(send_button); //3
    lay->addWidget(error_label); //4
    lay->addWidget(text_ip); //5
    lay->addWidget(port); //6
    lay->addWidget(fileName_text); //7
    lay->addWidget(applyText); //8
    lay->addWidget(packetNumber);//9

    this->setLayout(lay);
}

void clientGUI::setAddrandPort()
{
    QLayoutItem* item=this->layout()->itemAt(5);
    if(item &&item->widget())
    {
        QTextEdit* text_ip=qobject_cast<QTextEdit*>(item->widget());
        if(text_ip)
        {
#ifdef DEBUG_LOG
            qDebug()<<text_ip->toPlainText();
#endif
            cli->setServAddr(QHostAddress(text_ip->toPlainText()));
        }
    }
    item=this->layout()->itemAt(6);
    if(item &&item->widget())
    {
        QTextEdit* port=qobject_cast<QTextEdit*>(item->widget());
        if(port)
        {
#ifdef DEBUG_LOG
            qDebug()<<port->toPlainText();
#endif
            cli->setServPort(quint16(port->toPlainText().toUShort()));
        }
    }
}

void clientGUI::setFile()
{
    QLayoutItem* item=this->layout()->itemAt(7);
    if(item &&item->widget())
    {
        QTextEdit* fileName=qobject_cast<QTextEdit*>(item->widget());
        if(fileName)
        {
#ifdef DEBUG_LOG
            qDebug()<<"FILENAME="<<fileName->toPlainText();
#endif
            cli->setFileName(fileName->toPlainText());
        }
    }

}

void clientGUI::updateError(const QString& error)
{
#ifdef DEBUG_LOG
    qDebug()<<error;
#endif
    QLayoutItem* item=this->layout()->itemAt(4);
    if(item &&item->widget())
    {
        QLabel* errorLab=qobject_cast<QLabel*>(item->widget());
        if(errorLab)
        {
            QString str("Errors: "+QString::number(cli->getErrorNumber()));
            errorLab->setText(str);
        }
    }
}

void clientGUI::updatePackets()
{
    QLayoutItem* item=this->layout()->itemAt(9);
    if(item &&item->widget())
    {
        QLabel* packetLab=qobject_cast<QLabel*>(item->widget());
        if(packetLab)
        {
            QString str("Successfuly sent packets = ["+QString::number(cli->getSuccessful())+
                        "/"+QString::number(cli->getAllPackets())+"]");
            packetLab->setText(str);
        }
    }
}
