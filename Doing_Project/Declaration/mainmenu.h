#ifndef MAINMENU_H
#define MAINMENU_H

#include <QDialog>
#include "mysql.h"
#include "inforofman.h"
#include "mainwindow.h"
#include "isolatedplace.h"
#include "tableview.h"

#include <vector>

namespace Ui {
class MainMenu;
}

class MainMenu : public QDialog
{
    Q_OBJECT

public:
    explicit MainMenu(QWidget *parent = nullptr);
    ~MainMenu();

private slots:
    void on_pushButtonNewDeclaration_clicked();

    void on_pushButtonSubmitOfDeclaration_clicked();

    void on_ButtonConnectDB_clicked();

    void on_btnExit_clicked();

    void on_btnSubmitOfIsolated_clicked();

    void on_btnResetIsolatedPlace_clicked();

    void on_pushButtonResetDeclaration_clicked();

    void on_btnDeleteAllValuesDeclaration_clicked();

    void on_btnDeleteAllValuesIsolated_clicked();

    void on_btnNewIsolatedPlace_clicked();

    void on_pushButtonUpdateDeclaration_clicked();

    void on_btnUpdateIsolatedPlace_clicked();

    void on_ButtonShowDB_clicked();

    void on_ButtonDropTB_Declaration_clicked();

    void on_ButtonDropTB_Isolated_clicked();

private:
    Ui::MainMenu *ui;
    InforOfMan manTable;
    IsolatedPlace isolatedTable;
    bool stateOfAddingDeclaration;
    bool stateOfUpdateDeclaration;

    bool stateOfAddingIsolated;
    bool stateOfUpdateIsolated;

    bool stateOfConnected;
};

#endif // MAINMENU_H
