#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include "manInforTable.h"
#include "isolated.h"
#include "login.h"

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

public:
    int settingUpDatabase();

private slots:
    void on_btnAddingNewDeOfMan_clicked();
    void on_btnSubmit_clicked();
    void on_btnOpenDB_clicked();

    void on_btnExit_clicked();

    void on_btnShowing_clicked();

    void on_btnIsolated_clicked();

    void on_tableView_activated(const QModelIndex &index);

    void on_comboBox_currentIndexChanged(const QString &arg1);

    void on_pushButton_load_clicked();

private:
    Ui::MainWindow *ui;
    Ui::Login *login;
    manInforTable *mManInforManage;
    isolated *mIsolatedPlacesManage;
};
#endif // MAINWINDOW_H
