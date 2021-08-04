#ifndef SQLITE_H
#define SQLITE_H

#include <QString>

class SQLITE
{
public:
    virtual ~SQLITE();
    virtual void OpenDB() = 0;
    virtual void CreateTable() = 0;
    virtual void InsertTable() = 0;
};

#endif // SQLITE_H
