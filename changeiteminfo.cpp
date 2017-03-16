#include "changeiteminfo.h"
#include "ui_changeiteminfo.h"

ChangeItemInfo::ChangeItemInfo(LMS* lms, QWidget *parent) :
    QDialog(parent),
    ui(new Ui::ChangeItemInfo)
{
    this->lms = lms;
    ui->setupUi(this);
    ui->ctitle->setEnabled(false);
    ui->csubject->setEnabled(false);
    ui->cauthor->setEnabled(false);
    ui->cisbn->setEnabled(false);
}

ChangeItemInfo::~ChangeItemInfo()
{
    delete ui;
}

void ChangeItemInfo::on_find_clicked()
{
    ui->text->clear();
    bool check = false;
    title = ui->title->text().toStdString();
    QSqlQuery query;
    if (query.exec("Select * from LibItems where Title = '"+QString::fromStdString(title)+"'"))
    {
        while (query.next())
        {
            isbn = query.value(0).toString().toStdString();
            subject = query.value(2).toString().toStdString();
            author = query.value(3).toString().toStdString();
            check = true;
            prevISBN = isbn;
        }
    }
    if (check == false)
    {
        ui->text->setText("Item Not Found");
        return;
    }
    ui->isbnLabel->setText(QString::fromStdString(isbn));
    ui->titleLabel->setText(QString::fromStdString(title));
    ui->subjectLabel->setText(QString::fromStdString(subject));
    ui->authorLabel->setText(QString::fromStdString(author));
    ui->ctitle->setEnabled(true);
    ui->csubject->setEnabled(true);
    ui->cauthor->setEnabled(true);
    ui->cisbn->setEnabled(true);
    if (author == "")
    {
        ui->authorLabel->hide();
        ui->cauthor->hide();
        ui->lineEdit_4->hide();
        ui->label_5->hide();
    }
}

void ChangeItemInfo::on_clear_clicked()
{
    ui->text->clear();
    ui->lineEdit->clear();
    ui->lineEdit_2->clear();
    ui->lineEdit_3->clear();
    ui->lineEdit_4->clear();
    ui->title->clear();
    ui->isbnLabel->clear();
    ui->titleLabel->clear();
    ui->subjectLabel->clear();
    ui->authorLabel->clear();
    ui->ctitle->setEnabled(false);
    ui->csubject->setEnabled(false);
    ui->cauthor->setEnabled(false);
    ui->cisbn->setEnabled(false);
}

void ChangeItemInfo::setValues()
{
    this->lms->changeInfo(prevISBN, isbn, title, subject, author);
    QSqlQuery query;
    if (query.exec("Select * from LibItems where Title = '"+QString::fromStdString(title)+"'"))
    {
        while (query.next())
        {
            isbn = query.value(0).toString().toStdString();
            subject = query.value(2).toString().toStdString();
            author = query.value(3).toString().toStdString();
        }
    }
    ui->isbnLabel->setText(QString::fromStdString(isbn));
    ui->titleLabel->setText(QString::fromStdString(title));
    ui->subjectLabel->setText(QString::fromStdString(subject));
    ui->authorLabel->setText(QString::fromStdString(author));
}

void ChangeItemInfo::on_back_clicked()
{
    this->hide();
    delete ui;
}

void ChangeItemInfo::on_cisbn_clicked()
{
    ui->text->clear();
    QSqlQuery query;
    if (ui->lineEdit->text().isEmpty())
    {
        ui->text->setText("Invalid ISBN");
        return;
    }
    query.exec("UPDATE LibItems SET ISBN = '"+QString::fromStdString(ui->lineEdit->text().toStdString())+"' "
                                      "WHERE ISBN = '"+QString::fromStdString(isbn)+"'");

    isbn = ui->lineEdit->text().toStdString();
    ui->text->setText("ISBN Changed");
    ui->lineEdit->clear();
    setValues();
    prevISBN = isbn;
}

void ChangeItemInfo::on_ctitle_clicked()
{
    ui->text->clear();
    QSqlQuery query;
    if (ui->lineEdit_2->text().isEmpty())
    {
        ui->text->setText("Invalid Title");
        return;
    }
    query.exec("UPDATE LibItems SET Title = '"+QString::fromStdString(ui->lineEdit_2->text().toStdString())+"' "
                                      "WHERE ISBN = '"+QString::fromStdString(isbn)+"'");
    title = ui->lineEdit_2->text().toStdString();
    ui->text->setText("Title Changed");
    ui->lineEdit_2->clear();
    setValues();
}

void ChangeItemInfo::on_csubject_clicked()
{
    ui->text->clear();
    QSqlQuery query;
    if (ui->lineEdit_3->text().isEmpty())
    {
        ui->text->setText("Invalid Subject");
        return;
    }
    query.exec("UPDATE LibItems SET Subject = '"+QString::fromStdString(ui->lineEdit_3->text().toStdString())+"' "
                                      "WHERE ISBN = '"+QString::fromStdString(isbn)+"'");
    subject = ui->lineEdit_3->text().toStdString();
    ui->text->setText("Subject Changed");
    ui->lineEdit_3->clear();
    setValues();
}

void ChangeItemInfo::on_cauthor_clicked()
{
    ui->text->clear();
    QSqlQuery query;
    if (ui->lineEdit_4->text().isEmpty())
    {
        ui->text->setText("Invalid Author");
        return;
    }
    query.exec("UPDATE LibItems SET Author = '"+QString::fromStdString(ui->lineEdit_4->text().toStdString())+"' "
                                      "WHERE ISBN = '"+QString::fromStdString(isbn)+"'");
    author = ui->lineEdit_4->text().toStdString();
    ui->text->setText("Author Changed");
    ui->lineEdit_4->clear();
    setValues();
}
