#ifndef DTOGENERATOR_H
#define DTOGENERATOR_H

#include <QDomDocument>
#include <QRandomGenerator>
#include <map>
#include <QDebug>
#include <iostream>
#include <string>
struct DTO_struct
{
    uint32_t id;
    uint32_t field;
    std::string name;
    std::map<std::string, std::string> key_value_params;
    uint32_t iq_arr_len;
    float* iq_example;
};
void printDTO(DTO_struct& str);

class DTOGenerator
{
public:
    DTOGenerator();
    ~DTOGenerator();
    DTO_struct generateStruct();
protected:
    void generateId();
    void generateField();
    std::string generateRandomString();
    void generateName();
    void generateMap();
    void generateArray();
    void clearArray();
private:
    DTO_struct str;
};

#endif // DTOGENERATOR_H
