#include "dtogenerator.h"

DTOGenerator::DTOGenerator()
{

}

DTOGenerator::~DTOGenerator()
{
    clearArray();
}

DTO_struct DTOGenerator::generateStruct()
{
    generateId();
    generateField();
    generateName();
    generateMap();
    generateArray();
    return str;
}

void DTOGenerator::generateId()
{
    str.id=QRandomGenerator::global()->bounded(quint32(0), quint32(-1)); //-1 = max unsigned value
}

void DTOGenerator::generateField()
{
    str.field=QRandomGenerator::global()->bounded(quint32(0), quint32(-1));
}

std::string DTOGenerator::generateRandomString()
{
    QString name;
    QString allowedCharacters="ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz0123456789";
    int namelength=QRandomGenerator::global()->bounded(1, 15+1);

    for(int i=0; i<namelength; ++i)
    {
        int index=QRandomGenerator::global()->bounded(allowedCharacters.length());
        name.append(allowedCharacters.at(index));
    }
    return name.toStdString();
}


void DTOGenerator::generateName()
{
    str.name=generateRandomString();
}

void DTOGenerator::generateMap()
{
    int mapLen=QRandomGenerator::global()->bounded(0, 100+1);
    std::pair<std::string, std::string> pr;
    for(int i=0; i<mapLen; ++i)
    {
        pr.first=generateRandomString();
        pr.second=generateRandomString();
        str.key_value_params.insert(pr);
    }
}

void DTOGenerator::generateArray()
{
    str.iq_arr_len=QRandomGenerator::global()->bounded(0, 1000+1);
    str.iq_example=new float[str.iq_arr_len];
    for(uint32_t i=0; i<str.iq_arr_len; ++i)
    {
        str.iq_example[i]=static_cast<float>(QRandomGenerator::global()->bounded(MAXFLOAT));
    }
}

void DTOGenerator::clearArray()
{
    if(str.iq_example)
    {
        delete[] str.iq_example;
    }
}

void printDTO(DTO_struct& str)
{
    qDebug()<<"id="<<str.id;
    qDebug()<<"field="<<str.field;
    qDebug()<<"name="<<QString::fromStdString(str.name);
    qDebug()<<"Map:";
    for(auto& item:str.key_value_params)
    {
        qDebug()<<QString::fromStdString(item.first)<<" : "<<QString::fromStdString(item.second);
    }
    qDebug()<<"arrayLen="<<str.iq_arr_len;
    for(uint32_t i=0; i<str.iq_arr_len; ++i)
    {
        qDebug()<<"Element №"<<i<<"="<<str.iq_example[i];
    }
}
