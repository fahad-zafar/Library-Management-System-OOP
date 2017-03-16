#include "additem.h"
#include "ui_additem.h"

AddItem::AddItem(LMS *lms, QWidget *parent) :
    QDialog(parent),
    ui(new Ui::AddItem)
{
    this->lms = lms;
    ui->setupUi(this);
}

AddItem::~AddItem()
{
    delete ui;
}

void AddItem::on_back_clicked()
{
    this->hide();
    delete ui;
}

void AddItem::on_add_clicked()
{
    string isbn = ui->id->text().toStdString();
    string title = ui->title->text().toStdString();
    string subject = ui->sub->text().toStdString();
    string author = ui->aut->text().toStdString();

    if ((isbn == "") || (title == "") || (subject == ""))
    {
        ui->text->setText("Incomplete Information");
        return;
    }

    QSqlQuery query;
    query.exec("INSERT INTO LibItems (ISBN, Title, Subject, Author, Loan) "
               "VALUES ('"+QString::fromStdString(isbn)+"', '"+QString::fromStdString(title)+"', "
               "'"+QString::fromStdString(subject)+"', '"+QString::fromStdString(author)+"', '"+QString::fromStdString("false")+"'); ");

    ui->text->setText("Item Added");
    ui->id->clear();
    ui->title->clear();
    ui->sub->clear();
    ui->aut->clear();
    if (author == "")
    {
        DVD temp (isbn, title, subject, this->lms);
        this->lms->addItem(&temp);
    }
    else
    {
        Book temp (isbn, title, subject, author, this->lms);
        this->lms->addItem(&temp);
    }
}
