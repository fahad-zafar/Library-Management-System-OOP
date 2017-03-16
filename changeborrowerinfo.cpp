#include "changeborrowerinfo.h"
#include "lms_singleton.h"
#include "ui_changeborrowerinfo.h"

ChangeBorrowerInfo::ChangeBorrowerInfo(LMS *lms, QWidget *parent) :
    QDialog(parent),
    ui(new Ui::ChangeBorrowerInfo)
{
    ui->setupUi(this);
    this->lms = lms;
    ui->cmob->setEnabled(false);
    ui->cuser->setEnabled(false);
    ui->cpass->setEnabled(false);
}

ChangeBorrowerInfo::~ChangeBorrowerInfo()
{
    delete ui;
}

void ChangeBorrowerInfo::on_back_clicked()
{
    this->hide();
    delete ui;
}

void ChangeBorrowerInfo::on_find_clicked()
{
    ui->text->clear();
    bool check = false;
    id = ui->title->text().toStdString();
    QSqlQuery query;
    if (query.exec("Select * from Borrowers where borID = '"+QString::fromStdString(id)+"'"))
    {
        while (query.next())
        {
            name = query.value(1).toString().toStdString();
            mob = query.value(2).toString().toStdString();
            username = query.value(3).toString().toStdString();
            password = query.value(4).toString().toStdString();
            check = true;
            prevID = id;
        }
    }
    if (check == false)
    {
        ui->text->setText("Borrower Not Found");
        return;
    }
    ui->nameL->setText(QString::fromStdString(name));
    ui->mobL->setText(QString::fromStdString(mob));
    ui->userL->setText(QString::fromStdString(username));
    ui->passL->setText(QString::fromStdString(password));
    ui->cmob->setEnabled(true);
    ui->cuser->setEnabled(true);
    ui->cpass->setEnabled(true);
}

void ChangeBorrowerInfo::on_clear_clicked()
{
    ui->text->clear();
    ui->lineEdit_2->clear();
    ui->lineEdit_3->clear();
    ui->lineEdit_4->clear();
    ui->title->clear();
    ui->nameL->clear();
    ui->mobL->clear();
    ui->userL->clear();
    ui->passL->clear();
    ui->cmob->setEnabled(false);
    ui->cuser->setEnabled(false);
    ui->cpass->setEnabled(false);
}

void ChangeBorrowerInfo::setValues()
{
    this->lms->changeUserInfo(id, mob);
    QSqlQuery query;
    if (query.exec("Select * from Borrowers where borID = '"+QString::fromStdString(id)+"'"))
    {
        while (query.next())
        {
            name = query.value(1).toString().toStdString();
            mob = query.value(2).toString().toStdString();
            username = query.value(3).toString().toStdString();
            password = query.value(4).toString().toStdString();
        }
    }
    ui->nameL->setText(QString::fromStdString(name));
    ui->mobL->setText(QString::fromStdString(mob));
    ui->userL->setText(QString::fromStdString(username));
    ui->passL->setText(QString::fromStdString(password));
}

void ChangeBorrowerInfo::on_cmob_clicked()
{
    ui->text->clear();
    QSqlQuery query;
    if (ui->lineEdit_2->text().isEmpty())
    {
        ui->text->setText("Invalid Mobile");
        return;
    }
    query.exec("UPDATE Borrowers SET borMobile = '"+QString::fromStdString(ui->lineEdit_2->text().toStdString())+"' "
                                      "WHERE borID = '"+QString::fromStdString(id)+"'");
    mob = ui->lineEdit_2->text().toStdString();
    ui->text->setText("Mobile Changed");
    ui->lineEdit_2->clear();
    setValues();
}

void ChangeBorrowerInfo::on_cuser_clicked()
{
    ui->text->clear();
    QSqlQuery query;
    if (ui->lineEdit_3->text().isEmpty())
    {
        ui->text->setText("Invalid UserName");
        return;
    }
    query.exec("UPDATE Borrowers SET borUsername = '"+QString::fromStdString(ui->lineEdit_3->text().toStdString())+"' "
                                      "WHERE borID = '"+QString::fromStdString(id)+"'");
    username = ui->lineEdit_3->text().toStdString();
    ui->text->setText("UserName Changed");
    ui->lineEdit_3->clear();
    setValues();
}

void ChangeBorrowerInfo::on_cpass_clicked()
{
    ui->text->clear();
    QSqlQuery query;
    if (ui->lineEdit_4->text().isEmpty())
    {
        ui->text->setText("Invalid PassWord");
        return;
    }
    query.exec("UPDATE Borrowers SET borPassword = '"+QString::fromStdString(ui->lineEdit_4->text().toStdString())+"' "
                                      "WHERE borID = '"+QString::fromStdString(id)+"'");
    password = ui->lineEdit_4->text().toStdString();
    ui->text->setText("PassWord Changed");
    ui->lineEdit_4->clear();
    setValues();
}
