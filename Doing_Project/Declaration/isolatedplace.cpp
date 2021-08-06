#include "isolatedplace.h"
#include "mainwindow.h"
#include "sqlite3.h"
#include <QtDebug>
#include <QMessageBox>

IsolatedPlace::IsolatedPlace()
{
    this->DirToDB = "";
    this->SqlCommand = "";
}

IsolatedPlace::IsolatedPlace(const std::string& DirToDB)
{
    this->DirToDB = DirToDB;
    this->SqlCommand = "";
}

IsolatedPlace::IsolatedPlace(const IsolatedPlace& _other)
{
    this->DirToDB = _other.DirToDB;
}

IsolatedPlace::~IsolatedPlace()
{
    this->DirToDB = "";
    this->SqlCommand = "";
}

int IsolatedPlace::openDatabase()
{
    int rc;
    sqlite3 * DB;
    rc = sqlite3_open(DirToDB.c_str(), &DB);

    if (rc != SQLITE_OK)
    {
        qDebug() << "Error connected to DB";
    }
    else
    {
        qDebug() << "Connected to DB successfully";
    }

    sqlite3_close(DB);

    return rc;
}

void IsolatedPlace::createTable()
{
    SqlCommand = "CREATE TABLE IF NOT EXISTS Isolated("
        "AreaID INT PRIMARY KEY NOT NULL,"
        "NameOfArea VARCHAR(255) NOT NULL,"
        "NumOfCases INT NOT NULL"
        ");"
        ;
    int rc;
    sqlite3 * DB;
    char * errMsg;
    rc = sqlite3_open(DirToDB.c_str(), &DB);
    if (rc != SQLITE_OK)
    {
        qDebug() << "Error: Failed to connect to DB" ;
    }

    rc = sqlite3_exec(DB,SqlCommand.c_str(),callback, 0, &errMsg);
    if (rc != SQLITE_OK)
    {
        qDebug() << "Error " << errMsg;
        sqlite3_free(errMsg);
    }
    else
    {
        qDebug() << "Created Isolated Table successful";
    }


    if (errMsg)
    {
        delete  errMsg;
        errMsg = nullptr;
    }

    // clear sqlCommand;
    reset();

    sqlite3_close(DB);
}

void IsolatedPlace::insertTable()
{
    int rc;
    sqlite3 * DB;
    char * errMsg;
    QMessageBox msgBox;

    rc = sqlite3_open(DirToDB.c_str(), &DB);
    if (rc != SQLITE_OK)
    {
        qDebug() << "Error: Failed to connect to DB" ;
    }

    // sqlCommand would create from outside.

    rc = sqlite3_exec(DB,SqlCommand.c_str(),callback, 0, &errMsg);

    if (rc != SQLITE_OK)
    {
        msgBox.setText("Error! Could not insert!");
        msgBox.defaultButton();
        msgBox.exec();
    }
    else
    {
        qDebug() << "Insert value into Isolated Table successful";
    }


    if (errMsg)
    {
        delete  errMsg;
        errMsg = nullptr;
    }

     // clear sqlCommand;
    reset();
    sqlite3_close(DB);
}

void IsolatedPlace::filterTable()
{

}

void IsolatedPlace::displayTable()
{

}

void IsolatedPlace::deleteValue()
{
    int rc;
    sqlite3 * DB;
    char * errMsg;
    QMessageBox msgBox;

    rc = sqlite3_open(DirToDB.c_str(), &DB);
    if (rc != SQLITE_OK)
    {
        qDebug() << "Error: Failed to connect to DB" ;
    }

    rc = sqlite3_exec(DB,SqlCommand.c_str(),callback, 0, &errMsg);
    if (rc != SQLITE_OK)
    {
        msgBox.setText("Error! Could not insert!");
        msgBox.defaultButton();
        msgBox.exec();
    }
    else
    {
        qDebug() << "Delete Values of Isolated Table successful";
    }


    if (errMsg)
    {
        delete  errMsg;
        errMsg = nullptr;
    }

     // clear sqlCommand;
    reset();
    sqlite3_close(DB);
}

void IsolatedPlace::updateValue()
{
    int rc;
    sqlite3 * DB;
    char * errMsg;
    QMessageBox msgBox;

    rc = sqlite3_open(DirToDB.c_str(), &DB);
    if (rc != SQLITE_OK)
    {
        qDebug() << "Error: Failed to connect to DB" ;
    }

    rc = sqlite3_exec(DB,SqlCommand.c_str(),callback, 0, &errMsg);
    if (rc != SQLITE_OK)
    {
        msgBox.setText("Error! Could not insert!");
        msgBox.defaultButton();
        msgBox.exec();
    }
    else
    {
        qDebug() << "Update Value of Isolated Table successful";
    }


    if (errMsg)
    {
        delete  errMsg;
        errMsg = nullptr;
    }

     // clear sqlCommand;
    reset();
    sqlite3_close(DB);
}


void IsolatedPlace::dropTable()
{
    int rc;
    sqlite3 * DB;
    char * errMsg;
    QMessageBox msgBox;

    rc = sqlite3_open(DirToDB.c_str(), &DB);
    if (rc != SQLITE_OK)
    {
        qDebug() << "Error: Failed to connect to DB" ;
    }

    // sqlCommand would create from outside.
    SqlCommand = "DROP TABLE IF EXISTS Isolated;";
    rc = sqlite3_exec(DB,SqlCommand.c_str(),callback, 0, &errMsg);

    if (rc != SQLITE_OK)
    {
        msgBox.setText("Error! Could not DROP!");
        msgBox.defaultButton();
        msgBox.exec();
    }
    else
    {
        qDebug() << "DROP Isolated Table successful";
    }


    if (errMsg)
    {
        delete  errMsg;
        errMsg = nullptr;
    }

     // clear sqlCommand;
    reset();
    sqlite3_close(DB);
}

void IsolatedPlace::reset()
{
    this->SqlCommand = "";
}

void IsolatedPlace::setDirToDB(const std::string& DirToDB)
{
    this->DirToDB = DirToDB;
}

std::string IsolatedPlace::getDirToDB()
{
    return this->DirToDB;
}

void IsolatedPlace::setSqlCommand(const std::string& sqlCommand)
{
    this->SqlCommand = sqlCommand;
}

std::string IsolatedPlace::getSqlCommand()
{
    return this->SqlCommand;
}

void IsolatedPlace::savingAddedValue(const ISOlATED& _value)
{
    this->ListValuesOfIsolated.push_back(_value);
}

std::vector<ISOlATED> IsolatedPlace::getListOfValues()
{
    return this->ListValuesOfIsolated;
}
