#include "xmlparser.h"

XMLParser::XMLParser(QObject *parent) : QObject(parent)
{

}

XMLParser::~XMLParser()
{

}

bool XMLParser::parseXML(const QString &filename, DTO_struct &dto)
{
    QFile file(filename);
    if(!file.open(QIODevice::ReadOnly))
    {
        emit parseError("Failed to open XML file!!");
        return false;
    }

    QXmlStreamReader xml(&file);

    while(!xml.atEnd()&&!xml.hasError())
    {
        QXmlStreamReader::TokenType token=xml.readNext();
        if(token==QXmlStreamReader::StartElement)
        {
            if(xml.name()=="id")
            {
                dto.id=xml.readElementText().toUInt();
            }
            else if(xml.name()=="field")
            {
                dto.field=xml.readElementText().toUInt();
            }
            else if(xml.name()=="name")
            {
                dto.name=xml.readElementText().toStdString();
            }
            else if(xml.name()=="map")
            {
                parseMap(xml, dto);
            }
            else if(xml.name()=="array")
            {
                parseArr(xml, dto);
            }
        }
    }
    file.close();
    return true;
}

bool XMLParser::generateXML(const QString& filename, DTO_struct &dto)
{
    QFile file(filename);
    if(!file.open(QIODevice::WriteOnly | QIODevice::Text))
    {
        emit parseError("Failed to open XML file ");
        return false;
    }

    QXmlStreamWriter xml(&file);
    xml.setAutoFormatting(true);
    xml.writeStartDocument();
    xml.writeStartElement("data");
    xml.writeTextElement("id", QString::number(dto.id));
    xml.writeTextElement("field", QString::number(dto.field));
    xml.writeTextElement("name", QString::fromStdString(dto.name));

    xml.writeStartElement("map");

    for(auto& item: dto.key_value_params)
    {
        xml.writeStartElement("entry");
        xml.writeAttribute("key", QString::fromStdString(item.first));
        xml.writeCharacters(QString::fromStdString(item.second));
        xml.writeEndElement();
    }
    xml.writeEndElement();

    xml.writeStartElement("array");
    xml.writeAttribute("size", QString::number(dto.iq_arr_len));
    for(uint32_t i=0; i<dto.iq_arr_len; ++i)
    {
        xml.writeTextElement("item", QString::number(dto.iq_example[i]));
    }

    xml.writeEndElement();

    xml.writeEndElement();

    xml.writeEndDocument();

    file.close();

    return true;
}

void XMLParser::parseMap(QXmlStreamReader &xml, DTO_struct &dto)
{
    std::pair<std::string, std::string> pr;
    while(!(xml.tokenType()==QXmlStreamReader::EndElement&&xml.name()=="map"))
    {
        xml.readNext();
        if(xml.tokenType()==QXmlStreamReader::StartElement && xml.name()=="entry")
        {
            pr.first=xml.attributes().value("key").toString().toStdString();
            xml.readNext();
            pr.second=xml.text().toString().toStdString();
            dto.key_value_params.insert(pr);
        }
    }
#ifdef DEBUG_LOG
    qDebug()<<"Map data:";
    for(auto it=dto.key_value_params.begin(); it!=dto.key_value_params.end(); ++it)
    {
        qDebug()<<QString::fromStdString(it->first)<<":"<<QString::fromStdString(it->second);
    }
#endif

}

void XMLParser::parseArr(QXmlStreamReader &xml, DTO_struct &dto)
{
    //uint32_t arraysize=0;
    QVector<float> array;
    if(xml.attributes().hasAttribute("size"))
    {
        dto.iq_arr_len=xml.attributes().value("size").toUInt();
    }
    dto.iq_example=new float[dto.iq_arr_len];
    while(!(xml.tokenType()==QXmlStreamReader::EndElement&&xml.name()=="array"))
    {
        xml.readNext();
        if(xml.tokenType()==QXmlStreamReader::StartElement && xml.name()=="item")
        {
            xml.readNext();
            //QString itemValue=xml.text().toFloat();
            //array.append(itemValue);
            array.push_back(xml.text().toFloat());
        }
    }
#ifdef DEBUG_LOG
    qDebug()<<"Array data:";
    qDebug()<<array;
#endif
    for(uint32_t i=0; i<dto.iq_arr_len; ++i)
    {
        dto.iq_example[i]=array[i];
    }
}
