#ifndef MYSQL_H
#define MYSQL_H

#include "sqlite3.h"
#include <iostream>

class mySQL
{
public:
    virtual ~mySQL() {}
    virtual int openDatabase() = 0;
    //virtual void closeDatabase() = 0;
    virtual void createTable() = 0;
    virtual void insertTable() = 0;
    virtual void filterTable() = 0;
    virtual void displayTable() = 0;
    virtual void deleteValue() = 0;
    virtual void updateValue() = 0;
    virtual void dropTable() = 0;
    virtual void reset() = 0;
};

#endif // MYSQL_H
