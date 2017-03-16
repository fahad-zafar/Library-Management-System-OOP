#ifndef RETURNITEM_H
#define RETURNITEM_H
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
class ReturnItem;
}

class ReturnItem : public QDialog
{
    Q_OBJECT

public:
    explicit ReturnItem(QWidget *parent = 0);
    ~ReturnItem();
    void setValues (LMS*, string, string, string);
    void setTable ();
    void fineCalculator ();

private slots:
    void on_pushButton_clicked();

    void on_details_clicked();

    void on_back_clicked();

private:
    Ui::ReturnItem *ui;
    Clerk obj;
    LMS* lms = new LMS ();
    string borID;
    string bookID;
    string issueDate;
    string returnDate;
};

#endif // RETURNITEM_H
