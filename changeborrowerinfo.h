#ifndef CHANGEBORROWERINFO_H
#define CHANGEBORROWERINFO_H
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
class ChangeBorrowerInfo;
}

class ChangeBorrowerInfo : public QDialog
{
    Q_OBJECT

public:
    explicit ChangeBorrowerInfo(LMS*, QWidget *parent = 0);
    ~ChangeBorrowerInfo();
    void setValues ();

private slots:

    void on_back_clicked();

    void on_find_clicked();

    void on_clear_clicked();

    void on_cmob_clicked();

    void on_cuser_clicked();

    void on_cpass_clicked();

private:
    Ui::ChangeBorrowerInfo *ui;
    string prevID, id, name, mob, username, password;
    LMS* lms = new LMS ();
};

#endif // CHANGEBORROWERINFO_H
