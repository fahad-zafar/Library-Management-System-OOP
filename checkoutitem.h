#ifndef CHECKOUTITEM_H
#define CHECKOUTITEM_H
#include <QtSql>
#include <QDebug>
#include <QFileInfo>
#include <QDialog>
#include "lms.h"
#include "clerk.h"
#include "book.h"
#include "borrower.h"

namespace Ui {
class CheckOutItem;
}

class CheckOutItem : public QDialog
{
    Q_OBJECT

public:
    explicit CheckOutItem(QWidget *parent = 0);
    ~CheckOutItem();
    void setValues (LMS*, string, string, string);
    void setTable ();

private slots:

    void on_back_clicked();

    void on_out_clicked();

private:
    Ui::CheckOutItem *ui;
    Clerk obj;
    LMS* lms = new LMS ();
    QSqlDatabase *myDB;
};

#endif // CHECKOUTITEM_H
