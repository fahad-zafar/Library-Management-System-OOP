#ifndef RETURNITEMWINDOW_H
#define RETURNITEMWINDOW_H
#include <QtSql>
#include <QDebug>
#include <QFileInfo>
#include <QDialog>

namespace Ui {
class ReturnItemWindow;
}

class ReturnItemWindow : public QDialog
{
    Q_OBJECT

public:
    explicit ReturnItemWindow(QWidget *parent = 0);
    ~ReturnItemWindow();

private slots:
    void on_pushButton_clicked();

    void on_pushButton_2_clicked();

private:
    Ui::ReturnItemWindow *ui;
    QSqlDatabase *myDB;
};

#endif // RETURNITEMWINDOW_H
