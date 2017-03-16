#ifndef BORROWERDATA_H
#define BORROWERDATA_H
#include <QtSql>
#include <QListWidget>
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
class BorrowerData;
}

class BorrowerData : public QDialog
{
    Q_OBJECT

public:
    explicit BorrowerData(QWidget *parent = 0);
    ~BorrowerData();
    void setValues (QString, QString, QString, vector<QString> &, QString, LMS*, QSqlDatabase*);


private slots:
    void on_signOut_clicked();

    void on_title_btn_2_clicked();

    void on_author_btn_2_clicked();

    void on_subject_btn_2_clicked();

    void on_details_clicked();

    void on_pay_clicked();

    void on_return_2_clicked();

    void itemClickedSlot(QListWidgetItem *);

    void itemClickedSlot2(QListWidgetItem *);

private:
    Ui::BorrowerData *ui;
    QSqlDatabase *myDB;
    Borrower obj;
    LMS* lms = new LMS ();
};

#endif // BORROWERDATA_H
