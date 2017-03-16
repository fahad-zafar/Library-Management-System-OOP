#ifndef DELITEM_H
#define DELITEM_H
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
class DelItem;
}

class DelItem : public QDialog
{
    Q_OBJECT

public:
    explicit DelItem(LMS*, QWidget *parent = 0);
    ~DelItem();

private slots:
    void on_pushButton_clicked();

    void on_back_clicked();

    void on_del_clicked();

private:
    Ui::DelItem *ui;
    LMS* lms = new LMS ();
};

#endif // DELITEM_H
