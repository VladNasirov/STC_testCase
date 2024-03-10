#ifndef XMLPARSER_H
#define XMLPARSER_H

#include <QObject>
#include <QXmlStreamReader>
#include "../dto/dtogenerator.h"
#include <QFile>

class XMLParser : public QObject
{
    Q_OBJECT
public:
    explicit XMLParser(QObject* parent=nullptr);
    ~XMLParser();
    bool parseXML(const QString& filename, DTO_struct& dto);
    bool generateXML(const QString& filename, DTO_struct& dto);
signals:
    void parseError(const QString& err);
private:
    void parseMap(QXmlStreamReader& xml, DTO_struct& dto);
    void parseArr(QXmlStreamReader& xml, DTO_struct& dto);
};

#endif // XMLPARSER_H
