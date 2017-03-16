#ifndef ADDBORROWER_H
#define ADDBORROWER_H
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
class AddBorrower;
}

class AddBorrower : public QDialog
{
    Q_OBJECT

public:
    explicit AddBorrower(LMS*, QWidget *parent = 0);
    ~AddBorrower();

private slots:
    void on_add_clicked();

    void on_back_clicked();

private:
    Ui::AddBorrower *ui;
    LMS* lms = new LMS ();
};

#endif // ADDBORROWER_H
