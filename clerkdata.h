#ifndef CLERKDATA_H
#define CLERKDATA_H
#include "LMS.h"
#include "Borrower.h"
#include "Loan.h"
#include "returnitem.h"
#include "renewitems.h"
#include "LMS_Singleton.h"
#include "itemdata.h"
#include "changeborrowerinfo.h"
#include "holdrequestswindow.h"
#include "checkoutitem.h"
#include "borrowerdata.h"
#include "addborrower.h"
#include "borrowerinfo.h"
#include "clerk.h"
#include <QDialog>
using namespace std;

namespace Ui {
class ClerkData;
}

class ClerkData : public QDialog
{
    Q_OBJECT

public:
    explicit ClerkData(QWidget *parent = 0);
    ~ClerkData();
    void setValues (QString, QString, QString, LMS*);

private slots:

    void on_ctitle_clicked();

    void on_cauthor_clicked();

    void on_csubject_clicked();

    void on_signOut_clicked();

    void on_pushButton_2_clicked();

    void on_pushButton_clicked();

    void on_pushButton_5_clicked();

    void on_pushButton_3_clicked();

    void on_pushButton_4_clicked();

    void on_pushButton_7_clicked();

    void itemClickedSlot(QListWidgetItem *);

    void on_details_clicked();

    void on_pushButton_6_clicked();

private:
    Ui::ClerkData *ui;
    Clerk obj;
    LMS* lms = new LMS ();
};

#endif // CLERKDATA_H
