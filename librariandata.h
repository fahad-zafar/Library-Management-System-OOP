#ifndef LIBRARIANDATA_H
#define LIBRARIANDATA_H
#include "LMS.h"
#include "Borrower.h"
#include "Loan.h"
#include "returnitem.h"
#include "renewitems.h"
#include "additem.h"
#include "delitem.h"
#include "changeiteminfo.h"
#include "LMS_Singleton.h"
#include "itemdata.h"
#include "changeborrowerinfo.h"
#include "holdrequestswindow.h"
#include "checkoutitem.h"
#include "borrowerdata.h"
#include "addborrower.h"
#include "borrowerinfo.h"
#include "librarian.h"
#include "clerk.h"
#include <QDialog>

namespace Ui {
class LibrarianData;
}

class LibrarianData : public QDialog
{
    Q_OBJECT

public:
    explicit LibrarianData(QWidget *parent = 0);
    ~LibrarianData();
    void setValues (QString, QString, QString, LMS*);

private slots:
    void on_addBor_clicked();

    void on_changeBo_clicked();

    void on_checkBor_clicked();

    void on_checkIn_clicked();

    void on_checkOut_clicked();

    void on_renew_clicked();

    void on_holdReq_clicked();

    void on_addItem_clicked();

    void on_changeItem_clicked();

    void on_delItem_clicked();

    void on_ctitle_clicked();

    void on_cauthor_clicked();

    void on_csubject_clicked();

    void on_signOut_clicked();

    void on_details_clicked();

    void itemClickedSlot(QListWidgetItem *);

    void on_totalFine_clicked();

private:
    Ui::LibrarianData *ui;
    Librarian obj;
    LMS* lms = new LMS ();
};

#endif // LIBRARIANDATA_H
