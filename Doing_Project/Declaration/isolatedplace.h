#ifndef ISOLATEDPLACE_H
#define ISOLATEDPLACE_H

#include "mysql.h"
#include <iostream>
#include <vector>
typedef struct IsolatedTable{
    std::string NameOfArea;
    std::string DangLevel;
    int AreaID;
    int NumberOfCases;
} ISOlATED;

class IsolatedPlace : public mySQL
{
private:
    std::string DirToDB;
    std::string SqlCommand;
    std::vector<ISOlATED> ListValuesOfIsolated;
public:
    IsolatedPlace();
    IsolatedPlace(const std::string& DirToDB);
    IsolatedPlace(const IsolatedPlace& _other);
    ~IsolatedPlace();
    int openDatabase();
    void createTable();
    void insertTable();
    void filterTable();
    void displayTable();
    void deleteValue();
    void updateValue();
    void dropTable();
    void reset();

    // set - get:
    void setDirToDB(const std::string& DirToDB);
    std::string getDirToDB();
    void setSqlCommand(const std::string& sqlCommand);
    std::string getSqlCommand();

    // saving added values
    void savingAddedValue(const ISOlATED& _value);
    std::vector<ISOlATED> getListOfValues();
};

#endif // ISOLATEDPLACE_H
