#ifndef CLIENTGUI_H
#define CLIENTGUI_H

#include <QWidget>
#include "client.h"
#include <QVBoxLayout>
#include <QPushButton>
#include <QLayout>
#include <QLabel>
#include <QTextEdit>
#include <QMap>
class clientGUI : public QWidget
{
    Q_OBJECT
public:
    explicit clientGUI(QWidget *parent = nullptr);

signals:
public slots:
    void setAddrandPort();
    //selectFileName
    void setFile();
    void updateError(const QString &error);
    void updatePackets();
private:
    Client* cli;
};

#endif // CLIENTGUI_H
