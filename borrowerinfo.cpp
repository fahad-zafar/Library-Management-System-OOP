#include "borrowerinfo.h"
#include "ui_borrowerinfo.h"

BorrowerInfo::BorrowerInfo(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::BorrowerInfo)
{
    ui->setupUi(this);
}

BorrowerInfo::~BorrowerInfo()
{
    delete ui;
}

void BorrowerInfo::on_find_clicked()
{
    bool check = false;
    string id = ui->id->text().toStdString();
    QSqlQuery query;
    if (query.exec("select * from Borrowers where borID = '"+QString::fromStdString(id)+"'"))
    {
        while (query.next()) {
            ui->text->clear();
            ui->name->setText(query.value(1).toString());
            ui->mob->setText(query.value(2).toString());
            ui->user->setText(query.value(3).toString());
            ui->pass->setText(query.value(4).toString());
            ui->fine->setText(query.value(5).toString());
            check = true;
        }
    }
    if (check == false)
    {
        ui->name->clear();
        ui->mob->clear();
        ui->user->clear();
        ui->pass->clear();
        ui->fine->clear();
        ui->text->setText("No Borrower Found");
    }
}

void BorrowerInfo::on_back_clicked()
{
    this->hide();
    delete ui;
}
