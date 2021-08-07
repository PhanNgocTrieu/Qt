#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "mainmenu.h"
#include "sqlite3.h"

#include <QDebug>
#include <QString>
#include <QMessageBox>
#include <QPixmap>
#include <QStyle>


MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    //ui->txtUserName->set
    QWidget::setWindowTitle("Login Window");
    QPixmap pix(":/resources/Image/Login.jpg");
    int width = ui->lblOfLoginPicture->width();
    int height = ui->lblOfLoginPicture->height();
    ui->lblOfLoginPicture->setPixmap(pix.scaled(width,height,Qt::KeepAspectRatio));

//    QPixmap pix2(":/resources/Image/SingIn-icon.jpg");
//    int width_signin = ui->groupSignIn->width();
//    int height_signin = ui->groupSignIn->height();



}

MainWindow::~MainWindow()
{
    delete ui;
}


void MainWindow::on_pushButtonLogin_clicked()
{
    QString userName = ui->txtUserName->text();
    QString password = ui->txtPassWord->text();

    if (userName == "1" && password == "1")
    {
        //QMessageBox::information(this,"Login","UserName and Password are correct");
        this->hide();
        MainMenu *ui_Menu = new MainMenu(this);
        ui_Menu->show();
        ui->txtUserName->setText("");
        ui->txtPassWord->setText("");
    }
    else
    {
         QMessageBox::warning(this,"Login","UserName and Password are incorrect");

    }

}

