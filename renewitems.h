#ifndef RENEWITEMS_H
#define RENEWITEMS_H
#include <QtSql>
#include <QDebug>
#include <QFileInfo>
#include <QDialog>
#include "lms.h"
#include "clerk.h"
#include "book.h"
#include "borrower.h"
using namespace std;

namespace Ui {
class RenewItems;
}

class RenewItems : public QDialog
{
    Q_OBJECT

public:
    explicit RenewItems(QWidget *parent = 0);
    ~RenewItems();
    void setValues (LMS*, string, string, string);
    void setTable ();
    void fineCalculator ();

private slots:
    void on_back_clicked();

    void on_renew_clicked();

    void on_calFine_clicked();

private:
    Ui::RenewItems *ui;
    Clerk obj;
    LMS* lms = new LMS ();
    string borID;
    string bookID;
    string issueDate;
    string returnDate;
};

#endif // RENEWITEMS_H
