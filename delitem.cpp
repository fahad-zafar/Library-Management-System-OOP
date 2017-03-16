#include "delitem.h"
#include "ui_delitem.h"

DelItem::DelItem(LMS* lms, QWidget *parent) :
    QDialog(parent),
    ui(new Ui::DelItem)
{
    ui->setupUi(this);
    ui->del->setEnabled(false);
    this->lms = lms;
}

DelItem::~DelItem()
{
    delete ui;
}

void DelItem::on_pushButton_clicked()
{
    ui->text->clear();
    string title = ui->title->text().toStdString();
    QSqlQuery query;
    int count = 0;
    if (query.exec("Select * from LibItems where Title = '"+QString::fromStdString(title)+"'"))
    {
        while (query.next())
        {
            count++;
            ui->isbn->setText(query.value(0).toString());
            ui->sub->setText(query.value(2).toString());
            if (query.value(3).toString().toStdString() == "")
            {
                ui->label_5->hide();
                ui->aut->hide();
            }
            else
                ui->aut->setText(query.value(3).toString());
            ui->del->setEnabled(true);
        }
    }
    if (count == 0)
    {
        ui->text->setText("Item Not Found");
        return;
    }
}

void DelItem::on_back_clicked()
{
    this->hide();
    delete ui;
}

void DelItem::on_del_clicked()
{
    QSqlQuery query;
    QString isbn = ui->isbn->text();
    query.exec ("Delete from Borrow_Requests where ISBN = '"+isbn+"'");
    query.exec ("Delete from Hold_Requests where ISBN = '"+isbn+"'");
    query.exec ("Delete from Items_Borrowed where ISBN = '"+isbn+"'");
    query.exec ("Delete from LibItems where ISBN = '"+isbn+"'");
    query.exec ("Delete from Loan_History where ISBN = '"+isbn+"'");
    query.exec ("Delete from Return_Requests where ISBN = '"+isbn+"'");

    LibItem* item = this->lms->getItemFromID(isbn.toStdString());
    this->lms->delItem(item);

    ui->aut->clear();
    ui->sub->clear();
    ui->isbn->clear();
    ui->title->clear();
    ui->del->setEnabled(false);
    ui->text->setText("Item Deleted");
}
