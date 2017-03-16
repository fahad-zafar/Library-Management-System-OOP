#ifndef HOLDREQUESTSWINDOW_H
#define HOLDREQUESTSWINDOW_H
#include <QtSql>
#include <QDebug>
#include <QFileInfo>
#include <QDialog>
#include "lms.h"
#include "clerk.h"
#include "book.h"
#include "borrower.h"

namespace Ui {
class HoldRequestsWindow;
}

class HoldRequestsWindow : public QDialog
{
    Q_OBJECT

public:
    explicit HoldRequestsWindow(QWidget *parent = 0);
    ~HoldRequestsWindow();
    void setValues (LMS*, string, string, string);
    void setTable ();

private slots:
    void on_back_clicked();

    void on_out_clicked();

private:
    Ui::HoldRequestsWindow *ui;
    Clerk obj;
    LMS* lms = new LMS ();
};

#endif // HOLDREQUESTSWINDOW_H
