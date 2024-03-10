#include <QApplication>
#include "clientgui.h"
int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    //IClient* cli= new Client(&a);
//    Client cli(&a);
//    QHostAddress addr("127.0.0.1");
//    quint16 port=2020;
//    cli.connectToServer(addr, port);
//    cli.generateFile("file.xml");
//    cli.clientSendData("file.xml");
//    cli.disconnect();
    //clientGUI* cliGui=new clientGUI(&a);
    clientGUI cliGui;
    cliGui.show();
    return a.exec();
}
