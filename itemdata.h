#ifndef ITEMDATA_H
#define ITEMDATA_H
#include <QtSql>
#include <QDebug>
#include <QFileInfo>
#include "LMS.h"
#include "Borrower.h"
#include "Loan.h"
#include "LMS_Singleton.h"
#include "book.h"
#include <QDialog>

namespace Ui {
class ItemData;
}

class ItemData : public QDialog
{
    Q_OBJECT

public:
    explicit ItemData(QWidget *parent = 0);
    ~ItemData();
    void setValues (User*, string, string, string, string, bool, LMS*, bool);

private slots:
    void on_hold_clicked();

    void on_request_clicked();

    void on_back_clicked();

    void on_renew_clicked();

private:
    Ui::ItemData *ui;
    User *user;
    LMS *lms = new LMS ();
    QSqlDatabase *myDB;
    Book obj;
};

#endif // ITEMDATA_H
