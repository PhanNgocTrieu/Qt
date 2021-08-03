#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QString> // working with Qstring (same string)
#include <QDebug>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    // Variables:
//    QString myStr = "Hello Guys!";
//    QString myStr2 = QString(10,'J');
//    QString myStr3;
//    QString myStr4 = "";

    /* Debug */
//    qDebug() << myStr; // this would like debug in another IDE - display on output
//    qDebug() << myStr2; // this would like debug in another IDE - display on output



    // Checking is Empty:
//    qDebug() << "\nChecking Empty:";
//    qDebug() << myStr.isEmpty();
//    qDebug() << myStr2.isEmpty();
//    qDebug() << myStr3.isEmpty();
//    qDebug() << myStr4.isEmpty();



     // Chekcking is Null:
//    qDebug() << "\nChecking NULL:";
//    qDebug() << myStr.isNull();
//    qDebug() << myStr2.isNull();
//    qDebug() << myStr3.isNull();
//    qDebug() << myStr4.isNull();

    /* Some methods in QString:

    startWith(<string>) : is start with <string>?
    endWith(<string>) : is end with <string>?
    contains(<string>) : is contain that <string>?
    chop(int n) : delete n characters at end
    clear(): erase all of character in string -> be null
    truncate(int n): reject all of characters start from n pos

    Concatenate  2 strings:
    --- Using '+' operator
    --- append(<string>) : adding at back
    --- prepend(<strring>) : adding at front

    Uppercase and Lowercase:
    --- toLower(): convert to lowercase
    --- toUpper(): convert to uppercase


    Number to string and string to number:
    --- number(int n): convert n to string
        number(int n, int base): convert n to int with base (2,10,16,...)
        Note: just using for integer
    --- setNum(_type n): convert n to string
        Note: can use for integer for float


    -- toInt()/toFloat()/toDouble(): convert string has number format to number
        Note: If your string is not all of number -> converting would be failed
    */

    // arg(int number) method:
    // convert to string and put it at %. pos
    // Example:

//    int day = 3;
//    int month = 8;
//    int year = 2021;
//    QString mDate = QString("Today is: %1/%2/%3").arg(day).arg(month).arg(year);
//    qDebug() << mDate << "\n";



    // this make Window by name hello guys
    this->setWindowTitle("Calculator");
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::on_btnCalculator_clicked()
{
    double numberA, numberB, result;
    numberA = ui->inputA->text().toDouble();
    numberB = ui->inputB->text().toDouble();

    result = numberA + numberB;

    ui->lblResult->setText(QString("Result: %1").arg(result));

}

