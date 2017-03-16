#ifndef MAINWINDOW_H
#define MAINWINDOW_H
#include <QMainWindow>
#include "borrowerdata.h"
#include "librariandata.h"
#include "clerkdata.h"
#include "LMS.h"
#include "Borrower.h"
#include "Clerk.h"
#include "Librarian.h"
#include "Book.h"
#include "DVD.h"

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    void setUpLMSVectors (LMS *);
    ~MainWindow();

private slots:
    void on_signin_clicked();

    void on_clear_clicked();

private:
    Ui::MainWindow *ui;
    LMS* obj = new LMS ();
    QSqlDatabase *myDB;
};

#endif // MAINWINDOW_H
