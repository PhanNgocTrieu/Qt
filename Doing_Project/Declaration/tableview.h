#ifndef TABLEVIEW_H
#define TABLEVIEW_H

#include <QDialog>
#include "inforofman.h"
#include "isolatedplace.h"
#include <QSqlDatabase>
#include <QSqlQueryModel>
#include <iostream>

namespace Ui {
class TableView;
}

class TableView : public QDialog
{
    Q_OBJECT

// more properties:
private:
    IsolatedPlace isolatedPlaces;
    InforOfMan manInfor;

public:
    explicit TableView(QWidget *parent = nullptr);
    explicit TableView(QWidget *parent = nullptr, const std::string& DirToDB = "");
    ~TableView();

private slots:
    void on_pushButtonLoadingDBDeclaration_clicked();

    void on_btnExit_clicked();

    void on_pushButtonLoadingDBIsolated_clicked();
private:
    Ui::TableView *ui;
    QSqlDatabase database;
    QSqlQueryModel * modal;
};

#endif // TABLEVIEW_H
