#ifndef CHANGEITEMINFO_H
#define CHANGEITEMINFO_H
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

namespace Ui {
class ChangeItemInfo;
}

class ChangeItemInfo : public QDialog
{
    Q_OBJECT

public:
    explicit ChangeItemInfo(LMS*, QWidget *parent = 0);
    ~ChangeItemInfo();
    void setValues ();

private slots:
    void on_find_clicked();

    void on_clear_clicked();

    void on_back_clicked();

    void on_cisbn_clicked();

    void on_ctitle_clicked();

    void on_csubject_clicked();

    void on_cauthor_clicked();

private:
    Ui::ChangeItemInfo *ui;
    LMS* lms = new LMS ();
    string prevISBN, isbn, title, subject, author;
};

#endif // CHANGEITEMINFO_H
