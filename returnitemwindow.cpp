#include "returnitemwindow.h"
#include "ui_returnitemwindow.h"

ReturnItemWindow::ReturnItemWindow(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::ReturnItemWindow)
{
    ui->setupUi(this);
}

ReturnItemWindow::~ReturnItemWindow()
{
    delete ui;
}

void ReturnItemWindow::on_pushButton_clicked()
{
    this->hide();
    delete ui;
}

void ReturnItemWindow::on_pushButton_2_clicked()
{

}
