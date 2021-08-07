#include "mainmenu.h"
#include "ui_mainmenu.h"
#include "mainwindow.h"
#include "inforofman.h"
#include "sqlite3.h"
#include <iostream>
#include <QtDebug>
#include <QMessageBox>
#include <string>
#include <vector>


int callback(void* Unused, int argc, char** argv, char** azColName)
{
    int i;
    for (i = 0; i < argc; i++)
    {
        printf("%s = %s", azColName[i], argv[i] ? argv[i] : NULL);
    }
    std::cout << std::endl;
    return 0;
}

MainMenu::MainMenu(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::MainMenu)
{
    ui->setupUi(this);
    QWidget::setWindowTitle("Declaration Window");
    // disable three input of Declaration
    ui->txtName->setEnabled(false);
    ui->txtManID->setEnabled(false);
    ui->txtLocation->setEnabled(false);

    // disable three input of Isolated
    ui->txtAreaID->setEnabled(false);
    ui->txtNameOfArea->setEnabled(false);
    ui->txtNumberOfCases->setEnabled(false);

    // state
    this->stateOfAddingDeclaration = false;
    this->stateOfUpdateDeclaration = false;
    this->stateOfAddingIsolated = false;
    this->stateOfUpdateIsolated = false;
    this->stateOfConnected = false;

}

MainMenu::~MainMenu()
{
    delete ui;
}

/* ************************ CONNECTED DATABASE ************************** */

void MainMenu::on_ButtonConnectDB_clicked()
{
    std::string myDirToDB;
    QString dirToDB = ui->txtDirOfDB->text();
    myDirToDB = dirToDB.toStdString();
    manTable.setDirToDB(myDirToDB);
    isolatedTable.setDirToDB(myDirToDB);

    if (myDirToDB == "")
    {
        QMessageBox::information(this,"Unconnected","Path is Empty! Connected To Database failed");
    }
    else
    {
        int rc;
        rc = manTable.openDatabase();
        if (rc == SQLITE_OK)
        {
            QMessageBox::information(this,"Connected","Connected To Database successful");
//            manTable.dropTable();
            manTable.createTable();
            //isolatedTable.dropTable();
            isolatedTable.createTable();
            this->stateOfConnected = true;

            // reset
            ui->txtDirOfDB->setText("");
        }
        else
            QMessageBox::information(this,"Unconnected","Connected To Database failed");
    }

}


/* ************************ ADDING NEW ************************** */
void MainMenu::on_pushButtonNewDeclaration_clicked()
{
    this->stateOfUpdateDeclaration = false;
    if (this->stateOfConnected == true)
    {
        this->stateOfAddingDeclaration = true;
        // Enable three input typing
        ui->txtName->setEnabled(true);
        ui->txtManID->setEnabled(true);
        ui->txtLocation->setEnabled(true);
    }
    else
    {

       QMessageBox::information(this,"Unconnected","Connected To Database first!");
    }
}


void MainMenu::on_btnNewIsolatedPlace_clicked()
{
    this->stateOfUpdateIsolated = false;

    if (this->stateOfConnected == true)
    {
        this->stateOfAddingIsolated = true;
        // Enable three input typing
        ui->txtAreaID->setEnabled(true);
        ui->txtNameOfArea->setEnabled(true);
        ui->txtNumberOfCases->setEnabled(true);
    }
    else
    {

        QMessageBox::information(this,"Unconnected","Connected To Database first!");
    }
}

/* ************************ END OF ADDING ************************** */




/* ************************ UPDATE ************************** */

void MainMenu::on_pushButtonUpdateDeclaration_clicked()
{
    // Makeing sure doing one work
    this->stateOfAddingDeclaration = false;

    if (this->stateOfConnected == true)
    {
        this->stateOfUpdateDeclaration = true;
        // Enable three input typing
        ui->txtManID->setEnabled(true);
        ui->txtName->setEnabled(true);
        ui->txtLocation->setEnabled(true);
    }
    else
    {

        QMessageBox::warning(this,"Connected","You did not connect to DB yet!");
    }
}


void MainMenu::on_btnUpdateIsolatedPlace_clicked()
{
    this->stateOfAddingIsolated = false;

    if (this->stateOfConnected == true)
    {
        this->stateOfUpdateIsolated = true;
        // Enable three input typing
        ui->txtAreaID->setEnabled(true);
        ui->txtNameOfArea->setEnabled(true);
        ui->txtNumberOfCases->setEnabled(true);
    }
    else
    {

        QMessageBox::warning(this,"Connected","You did not connect to DB yet!");
    }
}

/* ************************ END OF UPDATE ************************** */




/* ************************ SUBMIT ************************** */

void MainMenu::on_pushButtonSubmitOfDeclaration_clicked()
{
    if (this->stateOfAddingDeclaration == true)
    {
        DECLARATION _Declaration;
        QString manID = ui->txtManID->text();
        QString name = ui->txtName->text();
        QString location = ui->txtLocation->text();

        _Declaration.manID = manID.toInt();
        _Declaration.Name = name.toStdString();
        _Declaration.Location = location.toStdString();


        std::string command;
        command = "INSERT INTO manInFor(manID, Name, Location) VALUES("
            + to_string(_Declaration.manID) + ", '" + _Declaration.Name + "', '" + _Declaration.Location + "');"
        ;

        std::cout << "Command: " << command << std::endl;
        manTable.setSqlCommand(command);
        manTable.insertTable();

        manTable.savingAddedValue(_Declaration);

        ui->txtName->setEnabled(false);
        ui->txtManID->setEnabled(false);
        ui->txtLocation->setEnabled(false);
        this->stateOfAddingDeclaration = false;


        // Checking in Isolated Places
        size_t len = isolatedTable.getListOfValues().size();
        vector<ISOlATED> locationList = isolatedTable.getListOfValues();

        for (size_t idex = 0; idex < len; idex++)
        {
            if (_Declaration.Location == locationList[idex].NameOfArea)
            {
                QMessageBox::warning(this,"In Isolated Place", QString::fromStdString("You in isolated place! Level: " + locationList[idex].DangLevel));
                break;
            }
        }

    }

    if (this->stateOfUpdateDeclaration == true)
    {
        std::string manID = ui->txtManID->text().toStdString();
        std::string name = ui->txtName->text().toStdString();
        std::string location = ui->txtLocation->text().toStdString();

        std::string command;
        command = "UPDATE manInFor SET Name = '" + name + "', Location = '" + location + "' WHERE manID = " + manID + ";";

        std::cout << "Command: " << command << std::endl;
        manTable.setSqlCommand(command);
        manTable.updateValue();
        ui->txtName->setEnabled(false);
        ui->txtManID->setEnabled(false);
        ui->txtLocation->setEnabled(false);
        this->stateOfUpdateDeclaration = false;
    }

    ui->txtManID->setText("");
    ui->txtName->setText("");
    ui->txtLocation->setText("");
}



void MainMenu::on_btnSubmitOfIsolated_clicked()
{
    if (stateOfAddingIsolated == true)
    {
        ISOlATED _Isolated;

        _Isolated.AreaID = ui->txtAreaID->text().toInt();
        _Isolated.NameOfArea = ui->txtNameOfArea->text().toStdString();
        _Isolated.NumberOfCases = ui->txtNumberOfCases->text().toInt();
        _Isolated.DangLevel = ui->txtLevel->text().toStdString();

        std::string command;
        command = "INSERT INTO Isolated(areaID, NameOfArea, NumOfCases, Level) VALUES("
            + to_string(_Isolated.AreaID) + ", '"
            +  _Isolated.NameOfArea + "', "
            + to_string(_Isolated.NumberOfCases) +", '"
            + _Isolated.DangLevel
            + "');"
        ;

        std::cout << "Command: " << command << std::endl;
        isolatedTable.setSqlCommand(command);

        isolatedTable.insertTable();

        isolatedTable.savingAddedValue(_Isolated);

        ui->txtAreaID->setEnabled(false);
        ui->txtNameOfArea->setEnabled(false);
        ui->txtNumberOfCases->setEnabled(false);
        stateOfAddingIsolated = false;
    }

    if(stateOfUpdateIsolated == true)
    {
        int AreaID = ui->txtAreaID->text().toInt();
        std::string NameOfArea = ui->txtNameOfArea->text().toStdString();
        int NumberOfCases = ui->txtNumberOfCases->text().toInt();


        std::string command;
        command = "UPDATE Isolated SET NameOfArea = '" + NameOfArea + "', NumOfCases = " + to_string(NumberOfCases) + " WHERE areaID = " + to_string(AreaID) + ";";

        std::cout << "Command: " << command << std::endl;
        isolatedTable.setSqlCommand(command);
        isolatedTable.updateValue();


        ui->txtAreaID->setEnabled(false);
        ui->txtNameOfArea->setEnabled(false);
        ui->txtNumberOfCases->setEnabled(false);
        this->stateOfUpdateIsolated = false;

    }
    ui->txtAreaID->setText("");
    ui->txtNameOfArea->setText("");
    ui->txtNumberOfCases->setText("");
}
/* ************************ END OF SUBMIT ************************** */




/* ************************ EXIT ************************** */

void MainMenu::on_btnExit_clicked()
{
    close();
}

/* ************************ END OF EXIT ************************** */





/* ************************ RESET ************************** */

void MainMenu::on_btnResetIsolatedPlace_clicked()
{
    ui->txtAreaID->setText("");
    ui->txtNameOfArea->setText("");
    ui->txtNumberOfCases->setText("");
}


void MainMenu::on_pushButtonResetDeclaration_clicked()
{
    ui->txtManID->setText("");
    ui->txtName->setText("");
    ui->txtLocation->setText("");
}

/* ************************ END OF RESET ************************** */




/* ************************ DELETE VALUES ************************** */

void MainMenu::on_btnDeleteAllValuesDeclaration_clicked()
{
    if (stateOfConnected)
    {
        std::string command;
        command = "DELETE FROM manInFor;";
        manTable.setSqlCommand(command);
        manTable.deleteValue();

        // clear all of value
        manTable.getListOfValues().clear();
    }
    else
    {

        QMessageBox::information(this,"Connected","You did not connect to DB yet!");
    }
}


void MainMenu::on_btnDeleteAllValuesIsolated_clicked()
{
    if (stateOfConnected == true)
    {
        std::string command;
        command = "DELETE FROM Isolated;";
        isolatedTable.setSqlCommand(command);
        isolatedTable.deleteValue();

        // clear all of value
        isolatedTable.getListOfValues().clear();
    }
    else
    {

        QMessageBox::information(this,"Connected","You did not connect to DB yet!");
    }
}

/* ************************ END OF DELETE ************************** */




/* ************************ Displaying ************************** */

void MainMenu::on_ButtonShowDB_clicked()
{
    if (stateOfConnected == true)
    {
        TableView *mTableDb = new TableView(this,manTable.getDirToDB());
        mTableDb->show();
    }
    else
    {
        QMessageBox::information(this,"Error:","You did not connect to DB yet!");
    }
}


void MainMenu::on_ButtonDropTB_Declaration_clicked()
{
    manTable.dropTable();
}


void MainMenu::on_ButtonDropTB_Isolated_clicked()
{
    isolatedTable.dropTable();
}

