#ifndef SERVERGUI_H
#define SERVERGUI_H

#include <QWidget>
#include "server.h"
#include <QVBoxLayout>
#include <QPushButton>
#include <QLayout>
#include <QLabel>
#include <QTextEdit>
#include <QMap>
class serverGUI : public QWidget
{
    Q_OBJECT
public:
    explicit serverGUI(QWidget *parent = nullptr);

signals:

public slots:
    void setAddrandPort();
    void setFile();
    void updateError(const QString &error);
    void updatePackets();
private:
    server* serv;
};

#endif // SERVERGUI_H
