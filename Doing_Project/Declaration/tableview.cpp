#include "tableview.h"
#include "ui_tableview.h"
#include "sqlite3.h"
#include <QTableView>
#include <QTableWidget>
#include <QSqlTableModel>
#include <QMessageBox>
#include <QAbstractItemModel>
#include <QSqlQueryModel>
#include <QSqlQuery>



TableView::TableView(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::TableView)
{
    ui->setupUi(this);
}

TableView::TableView(QWidget *parent, const std::string& DirToDB) :
    QDialog(parent),
    ui(new Ui::TableView)
{
    manInfor.setDirToDB(DirToDB);
    isolatedPlaces.setDirToDB(DirToDB);
    ui->setupUi(this);
}

TableView::~TableView()
{
    delete ui;
}

void TableView::on_pushButtonLoadingDBDeclaration_clicked()
{
    database = QSqlDatabase::addDatabase("QSQLITE");
    std::cout << manInfor.getDirToDB() << std::endl;
    database.setDatabaseName(QString::fromStdString(manInfor.getDirToDB()));
    if (database.open())
    {
        QSqlQueryModel * modal = new QSqlQueryModel();
        QSqlQuery* query = new QSqlQuery(database);

        query->prepare("select * from manInFor");

        if (query->exec())
        {
            modal->setQuery(*query);
            ui->tableViewBDDeclaration->setModel(modal);
            database.removeDatabase(QString::fromStdString(manInfor.getDirToDB()));
            qDebug() << "Row Count:" << (modal->rowCount());
            modal->clear();
        }
        else
        {
            qDebug() << "Query executive failed";
            modal->clear();
        }


    }
    else
    {
        std::cout << __LINE__ << std::endl;
        QMessageBox msg;
        msg.setText("Could not connect to DB to showing DB!");
        msg.defaultButton();
        msg.exec();
    }
}



void TableView::on_pushButtonLoadingDBIsolated_clicked()
{
    database = QSqlDatabase::addDatabase("QSQLITE");
    std::cout << isolatedPlaces.getDirToDB() << std::endl;
    database.setDatabaseName(QString::fromStdString(manInfor.getDirToDB()));
    if (database.open())
    {
        QSqlQueryModel * modal = new QSqlQueryModel();
        QSqlQuery* query = new QSqlQuery(database);

        query->prepare("select * from manInFor");

        if (query->exec())
        {
            modal->setQuery(*query);
            ui->tableViewBDDeclaration->setModel(modal);
            database.removeDatabase(QString::fromStdString(manInfor.getDirToDB()));
            qDebug() << "Row Count:" << (modal->rowCount());
            modal->clear();
        }
        else
        {
            qDebug() << "Query executive failed";
            modal->clear();
        }


    }
    else
    {
        std::cout << __LINE__ << std::endl;
        QMessageBox msg;
        msg.setText("Could not connect to DB to showing DB!");
        msg.defaultButton();
        msg.exec();
    }
}



void TableView::on_btnExit_clicked()
{
    close();
}
