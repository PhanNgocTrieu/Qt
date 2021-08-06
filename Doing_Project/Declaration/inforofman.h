
#ifndef INFOROFMAN_H
#define INFOROFMAN_H

#include "mysql.h"
#include "sqlite3.h"
#include <iostream>
#include <vector>

typedef struct inforOfManTable
{
    int manID;
    std::string Name;
    std::string Location;
} DECLARATION;

class InforOfMan : public mySQL
{
private:
    std::string mDirToDB;
    std::string mSqlCommand;
    std::vector<DECLARATION> ListValuesOfDeclaration;
public:
    InforOfMan();
    InforOfMan(const std::string& DirToDB);
    InforOfMan(const InforOfMan& _other);
    ~InforOfMan();

    int openDatabase();

    //void closeDatabase();
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

    // put value for saving
    void savingAddedValue(const DECLARATION& _value);
    std::vector<DECLARATION> getListOfValues();

};

#endif // INFOROFMAN_H
