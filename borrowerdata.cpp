#include "borrowerdata.h"
#include "ui_borrowerdata.h"
#include "ui_mainwindow.h"
#include "lms_singleton.h"
#include <QDebug>

BorrowerData::BorrowerData(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::BorrowerData)
{
    ui->setupUi(this);
    connect(ui->listWidget, SIGNAL(itemClicked(QListWidgetItem *)), this, SLOT(itemClickedSlot2(QListWidgetItem *)));
    ui->return_2->setEnabled(false);
    ui->details->setEnabled(false);
}

BorrowerData::~BorrowerData()
{
    delete ui;
}

void BorrowerData::setValues(QString id, QString name, QString mob, vector <QString>& books, QString fine, LMS *lms, QSqlDatabase *db)
{
    this->lms = lms;
    this->myDB = db;
    ui->stuID->setText(id);
    ui->stuName->setText(name);
    ui->stuMob->setText(mob);
    ui->stuFine->setText(fine);
    obj.setLMSReference(lms);
    obj.setUserID(id.toStdString());
    obj.setUserName(name.toStdString());
    obj.setMobileNumber(mob.toStdString());
    obj.setFine(fine.toDouble());

    for (int i = 0; i < books.size(); i++)
        ui->listWidget->addItem(books.at(i));
}

void BorrowerData::on_signOut_clicked()
{
    this->hide();
    delete ui;
}

void BorrowerData::on_title_btn_2_clicked()
{
    ui->listWidget_2->clear();
    ui->author_2->clear();
    ui->subject_2->clear();
    string input = ui->title_2->text().toStdString();
    bool val = obj.searchByTitle(input);
    if (val) {
        ui->label_6->setText("Book(s) Found");
        vector <string> items = obj.getItemsFromTitle(input);
        for (int i = 0; i < items.size(); i++)
            ui->listWidget_2->addItem(QString::fromStdString(items.at(i)));
        connect(ui->listWidget_2, SIGNAL(itemClicked(QListWidgetItem *)), this, SLOT(itemClickedSlot(QListWidgetItem *)));
    }
    else
        ui->label_6->setText("No Book Found");
}

void BorrowerData::on_author_btn_2_clicked()
{
    ui->title_2->clear();
    ui->subject_2->clear();
    ui->listWidget_2->clear();
    string input = ui->author_2->text().toStdString();
    bool val = obj.searchByAuthor(input);
    if (val) {
        ui->label_6->setText("Book(s) Found");
        vector <string> items = obj.getItemsFromAuthor(input);
        for (int i = 0; i < items.size(); i++)
            ui->listWidget_2->addItem(QString::fromStdString(items.at(i)));
        connect(ui->listWidget_2, SIGNAL(itemClicked(QListWidgetItem *)), this, SLOT(itemClickedSlot(QListWidgetItem *)));
    }
    else
        ui->label_6->setText("No Book Found");
}

void BorrowerData::on_subject_btn_2_clicked()
{
    ui->title_2->clear();
    ui->author_2->clear();
    ui->listWidget_2->clear();
    string input = ui->subject_2->text().toStdString();
    bool val = obj.searchBySubject(input);
    if (val) {
        ui->label_6->setText("Book(s) Found");
        vector <string> items = obj.getItemsFromSubject(input);
        for (int i = 0; i < items.size(); i++)
            ui->listWidget_2->addItem(QString::fromStdString(items.at(i)));
        connect(ui->listWidget_2, SIGNAL(itemClicked(QListWidgetItem *)), this, SLOT(itemClickedSlot(QListWidgetItem *)));
    }
    else
        ui->label_6->setText("No Book Found");
}

void BorrowerData::itemClickedSlot (QListWidgetItem * itemClicked)
{
    ui->details->setEnabled(true);
}

void BorrowerData::itemClickedSlot2 (QListWidgetItem * itemClicked)
{
    ui->return_2->setEnabled(true);
}

void BorrowerData::on_details_clicked()
{
    ui->details->setEnabled(false);
    string title = ui->listWidget_2->currentItem()->text().toStdString();
    ItemData itemobj;
    LibItem* temp = new LibItem ();
    temp = this->lms->getItem(title);
    bool val = false;
    QSqlQuery query;
    if (query.exec("Select * from LibItems where Title = '"+QString::fromStdString(title)+"'"))
    {
        while (query.next()) {
            if (query.value(4).toString().toStdString() == "true")
                val = true;
        }
    }
    itemobj.setValues(&obj, temp->getItemID(), temp->getItemTitle(), temp->getItemSubject(), temp->getItemAuthor(), val, this->lms, false);
    itemobj.exec();
}

void BorrowerData::on_pay_clicked()
{
    double fine = ui->stuFine->text().toDouble();
    double userEntered = ui->money->text().toDouble();
    if ((userEntered > fine) || (userEntered < 1) || (fine - userEntered < 0))
        ui->fineinfo->setText("Invalid Figure Entered");
    else
    {
        fine = fine - userEntered;
        lms->setFineCollected(userEntered);
        ui->fineinfo->setText("Fine Paid");
    }
    ui->stuFine->setText(QString::number(fine));

    QString id = QString::fromStdString(obj.getUserID());
    QString f = QString::number(fine);
    QSqlQuery query;
    query.exec("UPDATE Borrowers SET Fine = '"+f+"' WHERE borID = '"+id+"'");
    double totalFine = this->lms->getCollectedFine();
    query.exec("UPDATE Librarians SET libFine = '"+QString::number(totalFine)+"'");
    ui->money->clear();
}

void BorrowerData::on_return_2_clicked()
{
    ui->return_2->setEnabled(false);
    int row = ui->listWidget->currentRow();
    string bookID = ui->listWidget->currentItem()->text().toStdString();
    QSqlQuery query;
    string id, isbn, issueDate, returnDate;
    if (query.exec("Select * from Items_Borrowed where borID = '"+QString::fromStdString(obj.getUserID())+"' AND "
                                              "ISBN = '"+QString::fromStdString(bookID)+"'"))
    {
        while (query.next())
        {
            id = query.value(0).toString().toStdString();
            isbn = query.value(1).toString().toStdString();
            issueDate = query.value(2).toString().toStdString();
            returnDate = query.value(3).toString().toStdString();
        }
    }
    query.exec("INSERT INTO Return_Requests (borID, ISBN, IssueDate, ReturnDate) VALUES ('"+QString::fromStdString(id)+"',  "
               "'"+QString::fromStdString(isbn)+"', '"+QString::fromStdString(issueDate)+"', '"+QString::fromStdString(returnDate)+"'); ");
    ui->label_6->setText("Your return request has been recorded");

    ui->listWidget->takeItem(row);
}
