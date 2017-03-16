#include "addborrower.h"
#include "ui_addborrower.h"

AddBorrower::AddBorrower(LMS *lms, QWidget *parent) :
    QDialog(parent),
    ui(new Ui::AddBorrower)
{
    ui->setupUi(this);
    this->lms = lms;
}

AddBorrower::~AddBorrower()
{
    delete ui;
}

void AddBorrower::on_add_clicked()
{
    string id = ui->id->text().toStdString();
    string name = ui->name->text().toStdString();
    string mob = ui->mob->text().toStdString();
    string user = ui->user->text().toStdString();
    string pass = ui->pass->text().toStdString();

    if ((id == "") || (name == "") || (mob == "") || (user == "") || (pass == ""))
    {
        ui->text->setText("Incomplete Information");
        return;
    }

    QSqlQuery query;
    query.exec("INSERT INTO Borrowers (borID, borName, borMobile, borUsername, borPassword) "
               "VALUES ('"+QString::fromStdString(id)+"', '"+QString::fromStdString(name)+"', "
               "'"+QString::fromStdString(mob)+"', '"+QString::fromStdString(user)+"', '"+QString::fromStdString(pass)+"'); ");
    ui->text->setText("Borrower Added");
    ui->id->clear();
    ui->name->clear();
    ui->mob->clear();
    ui->user->clear();
    ui->pass->clear();

    Borrower temp (id, name, mob, 0, this->lms);
    this->lms->addUser(&temp);
}

void AddBorrower::on_back_clicked()
{
    this->hide();
    delete ui;
}
