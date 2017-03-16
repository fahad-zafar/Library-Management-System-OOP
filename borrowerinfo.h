#ifndef BORROWERINFO_H
#define BORROWERINFO_H
#include <QtSql>
#include <QDebug>
#include <QFileInfo>
#include "LMS.h"
#include "Borrower.h"
#include "Loan.h"
#include "LMS_Singleton.h"
#include "itemdata.h"
#include "borrower.h"
#include <QDialog>
using namespace std;

namespace Ui {
class BorrowerInfo;
}

class BorrowerInfo : public QDialog
{
    Q_OBJECT

public:
    explicit BorrowerInfo(QWidget *parent = 0);
    ~BorrowerInfo();

private slots:
    void on_find_clicked();

    void on_back_clicked();

private:
    Ui::BorrowerInfo *ui;
    QSqlDatabase *myDB;
};

#endif // BORROWERINFO_H
