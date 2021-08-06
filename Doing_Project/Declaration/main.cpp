#include "mainwindow.h"

#include <QApplication>
#include <iostream>
#include "sqlite3.h"
#include <stdio.h>



int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    MainWindow w;
    w.show();
    return a.exec();


//    QString mQString = "E:\\File_Documents\\Qt\\Qt_Project\\Declaration\\myDB.db";
//    std::string mString = mQString.toStdString();
//    std::cout << mString << endl;

//    sqlite3* DB;
//    int rc;
//    char * errMsg;
//    rc = sqlite3_open(mString.c_str(),&DB);
//    if (rc != SQLITE_OK)
//    {
//        std::cout << "Error: Could not open!" << std::endl;
//    }
//    else
//    {
//        std::cout << "Open DB successfully!\n";
//    }

//    std::string sqlCommand;
//    sqlCommand = "CREATE TABLE IF NOT EXISTS Isolated("
//            "areaID INT PRIMARY KEY NOT NULL,"
//            "namOfArea VARCHAR(255) NOT NULL,"
//            "numOfCases INT"
//            ");"
//            ;

//    rc = sqlite3_exec(DB,sqlCommand.c_str(),callback, 0 ,&errMsg);
//    if (rc != SQLITE_OK)
//    {
//        std::cout << "Error: Could not open! Error: " << *errMsg << endl;
//    }
//    else
//    {
//        std::cout << "Open DB successfully!\n";
//    }


    return 0;
}
