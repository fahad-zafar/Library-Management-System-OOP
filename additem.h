#ifndef ADDITEM_H
#define ADDITEM_H
#include <QtSql>
#include <QDebug>
#include <QFileInfo>
#include "dvd.h"
#include "book.h"
#include "LMS.h"
#include "Borrower.h"
#include "Loan.h"
#include "LMS_Singleton.h"
#include "itemdata.h"
#include "borrower.h"
#include <QDialog>

namespace Ui {
class AddItem;
}

class AddItem : public QDialog
{
    Q_OBJECT

public:
    explicit AddItem(LMS*, QWidget *parent = 0);
    ~AddItem();

private slots:
    void on_back_clicked();

    void on_add_clicked();

private:
    Ui::AddItem *ui;
    LMS* lms = new LMS ();
};

#endif // ADDITEM_H
