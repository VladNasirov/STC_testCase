#include <QApplication>
#include "servergui.h"
int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    serverGUI servGUI;
    servGUI.show();
    return a.exec();
}
