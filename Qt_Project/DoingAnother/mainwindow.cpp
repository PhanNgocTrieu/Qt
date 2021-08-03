#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    connect(ui->btnExit,SIGNAL(clicked()),this,SLOT(close()));
    connect(ui->btnHello,SIGNAL(clicked()),this,SLOT(DisplayText()));
}

MainWindow::~MainWindow()
{
    delete ui;
}

 void MainWindow::DisplayText()
 {
     ui->lblSayHello->setText("Hello Everyone From John!");
 }
