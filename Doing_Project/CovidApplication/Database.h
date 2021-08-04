#ifndef DATABASE_H
#define DATABASE_H

#include <QDialog>

namespace Ui {
class Database;
}

class Database : public QDialog
{
    Q_OBJECT

private slots:


public:
    explicit Database(QWidget *parent = nullptr);
    ~Database();

private:
    Ui::Database *ui;
};

#endif // DATABASE_H
