#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <iostream>
#include <QMessageBox>
#include <QtDebug>
#include <QSqlDatabase>
#include <QSqlQuery>
#include <QSqlDriver>
#include <QSqlTableModel>
#include <QSqlQueryModel>
#include <QSqlRelationalTableModel>
#include <QApplication>
#include <QSqlTableModel>
#include <QTableView>
#include <QSqlRecord>
#include <stdlib.h>
#include <QSqlError>

using namespace std;

// Default state:
bool stateOfAddingOfMan = false;
bool stateOfAddingOfIsp = false;
bool stateOfDeleteOfMan = false;
bool stateOfDeleteOfIsp = false;

void initializeModel(QSqlTableModel *model)
{
    model->setTable("person");
    model->setEditStrategy(QSqlTableModel::OnManualSubmit);
    model->select();

    model->setHeaderData(0, Qt::Horizontal, QObject::tr("manID"));
    model->setHeaderData(1, Qt::Horizontal, QObject::tr("Name"));
    model->setHeaderData(2, Qt::Horizontal, QObject::tr("Location"));
}

QTableView *createView(QSqlTableModel *model, const QString &title = "")
{
    QTableView *view = new QTableView;
    view->setModel(model);
    view->setWindowTitle(title);
    return view;
}


MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow), mManInforManage{nullptr}, mIsolatedPlacesManage{nullptr}
{
    ui->setupUi(this);
    ui->textnameOfMan->setEnabled(false);
    ui->textLocation->setEnabled(false);
}

MainWindow::~MainWindow()
{
    delete ui;
    if (mManInforManage)
        delete mManInforManage;
    if (mIsolatedPlacesManage)
       delete mIsolatedPlacesManage;
}

int MainWindow::settingUpDatabase()
{
    mManInforManage->connectToDB();
    mManInforManage->droptable();
    mManInforManage->createTable();

    mIsolatedPlacesManage->droptable();
    mIsolatedPlacesManage->createTable();

    return 0;
}


void MainWindow::on_btnAddingNewDeOfMan_clicked()
{
    ui->textLocation->setEnabled(true);
    ui->textnameOfMan->setEnabled(true);
    stateOfAddingOfMan = true;
}


void MainWindow::on_btnSubmit_clicked()
{
    ui->textLocation->setEnabled(false);
    ui->textnameOfMan->setEnabled(false);
}


void MainWindow::on_btnOpenDB_clicked()
{
    QString dirOfDB = ui->textNameOfDB->text();
    QMessageBox msgBox;
    if (dirOfDB.isEmpty() || dirOfDB.isNull())
    {
        msgBox.setText("Could not find out this directory! Please enter right dir");
        msgBox.setDefaultButton(QMessageBox::Ok);
    }

    QSqlDatabase db = QSqlDatabase::addDatabase("QSQLITE");
    db.setDatabaseName(dirOfDB);


    if (!db.open())
    {
        msgBox.setText("Failed to connect to DB");
        msgBox.setDefaultButton(QMessageBox::Ok);
        msgBox.exec();
    }
    else
    {
        msgBox.setText("Success to connect to DB");
        msgBox.setDefaultButton(QMessageBox::Ok);
        msgBox.exec();
    }
    //qDebug() << "Line: " << __LINE__ << "\n";
}


void MainWindow::on_btnExit_clicked()
{
    close();
}


void MainWindow::on_btnShowing_clicked()
{
    QSqlQueryModel *model = new QSqlQueryModel;
    QSqlQueryModel *model2 = new QSqlQueryModel;
    model->setQuery("SELECT * FROM manInFor;");
    model2->setQuery("SELECT * FROM Isolated;");
    QTableView *view = new QTableView;
    view->setModel(model);
    view->hideColumn(0);
    view->show();

    QTableView *view2 = new QTableView;
    view2->setModel(model);
    view->hideColumn(0);
    view2->show();
    // Can Edit
//    QSqlTableModel *model = new QSqlTableModel;
//    QSqlTableModel *model2 = new QSqlTableModel;
//    model->setTable("manInFor");
//    model->setEditStrategy(QSqlTableModel::OnManualSubmit);
//    model->select();
//    model->setHeaderData(0, Qt::Horizontal, tr("ManID"));
//    model->setHeaderData(1, Qt::Horizontal, tr("Name"));
//    model->setHeaderData(2, Qt::Horizontal, tr("Location"));

//    model2->setTable("Isolated");
//    model2->setEditStrategy(QSqlTableModel::OnManualSubmit);
//    model2->select();
//    model2->setHeaderData(0, Qt::Horizontal, tr("areaID"));
//    model2->setHeaderData(1, Qt::Horizontal, tr("namOfArea"));
//    QTableView *view2 = new QTableView;
//    view2->setModel(model2;
//    view2->show();
}


void MainWindow::on_btnIsolated_clicked()
{
    QSqlQueryModel *model = new QSqlQueryModel;
    model->setQuery("SELECT * FROM manInFor WHERE Location IN (SELECT namOfArea FROM Isolated);");

    QTableView *view = new QTableView;
    view->setModel(model);
    view->show();
}


void MainWindow::on_tableView_activated(const QModelIndex &index)
{

    QSqlDatabase db = QSqlDatabase::addDatabase("QSQLITE");
    db.setDatabaseName("E:\\File_Documents\\vsCode\\Sqlite\\VS2019\\Project\\CovidDeclaration\\CovidDeclaration\\myDB.db");
    db.open();

    QString var = ui->tableView->model()->data(index).toString();
    QSqlQuery sqlCommand;
    sqlCommand.prepare("SELECT * FROM manInFor WHERE manID = '" + var + "' or Name = '" + var + "' or Location = " + var + "'");

    if (sqlCommand.exec())
    {
        while(sqlCommand.next())
        {
            ui->textManID->setText(sqlCommand.value(0).toString());
            ui->textnameOfMan->setText(sqlCommand.value(1).toString());
            ui->textLocation->setText(sqlCommand.value(2).toString());
        }
    }
    else
    {
        QMessageBox::critical(this,tr("Error::"), sqlCommand.lastError().text());
    }
}


void MainWindow::on_comboBox_currentIndexChanged(const QString &arg1)
{
    QSqlDatabase db = QSqlDatabase::addDatabase("QSQLITE");
    db.setDatabaseName("E:\\File_Documents\\vsCode\\Sqlite\\VS2019\\Project\\CovidDeclaration\\CovidDeclaration\\myDB.db");
    db.open();

    QString var = ui->comboBox->currentText();
    QSqlQuery sqlCommand;
    sqlCommand.prepare("SELECT * FROM manInFor WHERE manID = '" + var + "'");

    if (sqlCommand.exec())
    {
        while(sqlCommand.next())
        {
            ui->textManID->setText(sqlCommand.value(0).toString());
            ui->textnameOfMan->setText(sqlCommand.value(1).toString());
            ui->textLocation->setText(sqlCommand.value(2).toString());
        }
    }
    else
    {
        QMessageBox::critical(this,tr("Error::"), sqlCommand.lastError().text());
    }
}


void MainWindow::on_pushButton_load_clicked()
{

}

