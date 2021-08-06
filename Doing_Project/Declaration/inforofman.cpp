#include "inforofman.h"
#include "mainwindow.h"
#include <iomanip>
#include <QtDebug>
#include <QMessageBox>

int callbackTitle(void* Unused, int argc, char** argv, char** azColName)
{
    int i;
    for (i = 0; i < argc; i++)
    {
        std::cout << left << setw(20) << setfill(' ') << azColName[i];
    }
    std::cout << "\n";

    return 0;
}

InforOfMan::InforOfMan()
{
    this->mDirToDB = "";
    this->mSqlCommand = "";
}

InforOfMan::InforOfMan(const std::string& DirToDB)
{
    this->mDirToDB = DirToDB;
    this->mSqlCommand = "";
}

InforOfMan::InforOfMan(const InforOfMan& _other)
{
    this->mDirToDB = _other.mDirToDB;
}

InforOfMan::~InforOfMan()
{
    mDirToDB = "";
    mSqlCommand = "";
}

int InforOfMan::openDatabase()
{
    int rc;
    sqlite3 * DB;
    rc = sqlite3_open(mDirToDB.c_str(), &DB);

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


void InforOfMan::createTable()
{
    mSqlCommand = "CREATE TABLE IF NOT EXISTS manInFor("
        "ManID INT PRIMARY KEY NOT NULL,"
        "Name VARCHAR(255) NOT NULL,"
        "Location VARCHAR(255) NOT NULL"
        ");"
        ;
    int rc;
    sqlite3 * DB;
    char * errMsg;
    rc = sqlite3_open(mDirToDB.c_str(), &DB);
    if (rc != SQLITE_OK)
    {
        qDebug() << "Error: Failed to connect to DB" ;
    }

    rc = sqlite3_exec(DB,mSqlCommand.c_str(),callback, 0, &errMsg);
    if (rc != SQLITE_OK)
    {
        qDebug() << "Error " << errMsg;
        sqlite3_free(errMsg);
    }
    else
    {
        qDebug() << "Created manInfor Table successful";
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

void InforOfMan::insertTable()
{
    int rc;
    sqlite3 * DB;
    char * errMsg;
    QMessageBox msgBox;
    rc = sqlite3_open(mDirToDB.c_str(), &DB);
    if (rc != SQLITE_OK)
    {
        qDebug() << "Error: Failed to connect to DB" ;
    }

    // sqlCommand would create from outside.

    if (mSqlCommand == "")
    {
        msgBox.setText("Empty Sqlcommand");
        msgBox.defaultButton();
        msgBox.exec();
    }

    rc = sqlite3_exec(DB,mSqlCommand.c_str(),callback, 0, &errMsg);
    if (rc != SQLITE_OK)
    {
        qDebug() << "Error " << errMsg;
        sqlite3_free(errMsg);
    }
    else
    {

        qDebug() << "Insert value into manInfor Table successful";
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

void InforOfMan::filterTable()
{

}

void InforOfMan::displayTable()
{

}

void InforOfMan::deleteValue()
{
    int rc;
    sqlite3 * DB;
    char * errMsg;
    QMessageBox msgBox;

    rc = sqlite3_open(mDirToDB.c_str(), &DB);
    if (rc != SQLITE_OK)
    {
        qDebug() << "Error: Failed to connect to DB" ;
    }

    rc = sqlite3_exec(DB,mSqlCommand.c_str(),callback, 0, &errMsg);
    if (rc != SQLITE_OK)
    {
        msgBox.setText("Error! Could not insert!");
        msgBox.defaultButton();
        msgBox.exec();
    }
    else
    {
        qDebug() << "Delete Values of manInfor Table successful";
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

void InforOfMan::updateValue()
{
    int rc;
    sqlite3 * DB;
    char * errMsg;
    QMessageBox msgBox;

    rc = sqlite3_open(mDirToDB.c_str(), &DB);
    if (rc != SQLITE_OK)
    {
        qDebug() << "Error: Failed to connect to DB" ;
    }

    rc = sqlite3_exec(DB,mSqlCommand.c_str(),callback, 0, &errMsg);
    if (rc != SQLITE_OK)
    {
        msgBox.setText("Error! Could not insert!");
        msgBox.defaultButton();
        msgBox.exec();
    }
    else
    {
        qDebug() << "Update Values of manInfor Table successful";
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

void InforOfMan::dropTable()
{
    int rc;
    sqlite3 * DB;
    char * errMsg;
    QMessageBox msgBox;

    rc = sqlite3_open(mDirToDB.c_str(), &DB);
    if (rc != SQLITE_OK)
    {
        qDebug() << "Error: Failed to connect to DB" ;
    }

    mSqlCommand = "DROP TABLE IF EXISTS manInfor;";
    rc = sqlite3_exec(DB,mSqlCommand.c_str(),callback, 0, &errMsg);
    if (rc != SQLITE_OK)
    {
        msgBox.setText("Error! Could not insert!");
        msgBox.defaultButton();
        msgBox.exec();
    }
    else
    {
        qDebug() << "Delete Values of manInfor Table successful";
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

void InforOfMan::reset()
{
    this->mSqlCommand = "";
}

void InforOfMan::setDirToDB(const std::string& DirToDB)
{
    this->mDirToDB = DirToDB;
}

std::string InforOfMan::getDirToDB()
{
    return this->mDirToDB;
}

void InforOfMan::setSqlCommand(const std::string& sqlCommand)
{
    this->mSqlCommand = sqlCommand;
}

std::string InforOfMan::getSqlCommand()
{
    return this->mSqlCommand;
}

void InforOfMan::savingAddedValue(const DECLARATION& _value)
{
    this->ListValuesOfDeclaration.push_back(_value);
}

std::vector<DECLARATION> InforOfMan::getListOfValues()
{
    return this->ListValuesOfDeclaration;
}
