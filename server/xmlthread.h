#ifndef XMLTHREAD_H
#define XMLTHREAD_H

#include <QObject>
#include <QThread>
#include "../dto/dtogenerator.h"
#include "../xml/xmlparser.h"
class XMLThread : public QThread
{
    Q_OBJECT
public:
    explicit XMLThread(QObject* parent=nullptr);
    void setFile(QString fileName);
public slots:
    void run();
signals:
    void finished();
    void error(const QString& error);
private:
    DTO_struct str;
    XMLParser par;
    QString filePath;
};

#endif // XMLTHREAD_H
