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
    QWidget::setWindowTitle("Database Window");
}

TableView::TableView(QWidget *parent, const std::string& DirToDB) :
    QDialog(parent),
    ui(new Ui::TableView)
{
    manInfor.setDirToDB(DirToDB);
    isolatedPlaces.setDirToDB(DirToDB);
    ui->setupUi(this);
    QWidget::setWindowTitle("Database Window");

    modal = new QSqlQueryModel();

}

TableView::~TableView()
{
    delete ui;
    modal->clear();
}

void TableView::on_pushButtonLoadingDBDeclaration_clicked()
{
    if (!database.isOpen())
    {
        database = QSqlDatabase::addDatabase("QSQLITE");
        std::cout << manInfor.getDirToDB() << std::endl;
        database.setDatabaseName(QString::fromStdString(manInfor.getDirToDB()));
    }
    if (database.open())
    {
        modal = new QSqlQueryModel();
        QSqlQuery* query = new QSqlQuery(database);

        query->prepare("select * from manInFor");

        if (query->exec())
        {
            modal->setQuery(*query);
            ui->tableViewBDDeclaration->setModel(modal);
            database.removeDatabase(QString::fromStdString(manInfor.getDirToDB()));
            qDebug() << "Row Count:" << (modal->rowCount());

        }
        else
        {
            qDebug() << "Query executive failed";
        }

        if (query)
        {
            delete query;
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
    if (!database.isOpen())
    {
        database = QSqlDatabase::addDatabase("QSQLITE");
        std::cout << manInfor.getDirToDB() << std::endl;
        database.setDatabaseName(QString::fromStdString(manInfor.getDirToDB()));
    }
    if (database.open())
    {
        modal = new QSqlQueryModel();
        QSqlQuery* query = new QSqlQuery(database);

        query->prepare("select * from Isolated");

        if (query->exec())
        {
            modal->setQuery(*query);
            ui->tableViewDBIsolated->setModel(modal);
            database.removeDatabase(QString::fromStdString(manInfor.getDirToDB()));
            qDebug() << "Row Count:" << (modal->rowCount());
        }
        else
        {
            qDebug() << "Query executive failed";
        }

        if (query)
        {
            delete query;
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



void TableView::on_pushButtonIsoLated_PeoPel_clicked()
{
    if (!database.isOpen())
    {
        database = QSqlDatabase::addDatabase("QSQLITE");
        std::cout << manInfor.getDirToDB() << std::endl;
        database.setDatabaseName(QString::fromStdString(manInfor.getDirToDB()));
    }

    if (database.open())
    {
        modal = new QSqlQueryModel();
        QSqlQuery* query = new QSqlQuery(database);

        query->prepare("select Name, location AS isolatedPlace from manInFor WHERE location in (SELECT NameOfArea from Isolated);");

        if (query->exec())
        {
            modal->setQuery(*query);
            ui->tableViewBDDeclaration->setModel(modal);
            database.removeDatabase(QString::fromStdString(manInfor.getDirToDB()));
            qDebug() << "Row Count:" << (modal->rowCount());
        }
        else
        {
            qDebug() << "Query executive failed";
        }

        if (query)
        {
            delete query;
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

