#include "itemdata.h"
#include "ui_itemdata.h"

ItemData::ItemData(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::ItemData)
{
    ui->setupUi(this);
}

void ItemData :: setValues(User* u, string  id, string title, string subject, string author, bool status, LMS * lms, bool borrower)
{
    obj.setItemID(id);
    obj.setItemTitle(title);
    obj.setItemAuthor(author);
    obj.setItemSubject(subject);
    obj.setItemReference(lms);

    this->user = u;
    this->lms = lms;

    ui->bookID->setText(QString::fromStdString(id));
    ui->bookTitle->setText(QString::fromStdString(title));
    ui->bookSubject->setText(QString::fromStdString(subject));
    ui->bookAuthor->setText(QString::fromStdString(author));

    ui->renew->hide();
    string UserWhoBorrowedID = "";
    QSqlQuery query;
    if (query.exec("Select borID from Items_Borrowed where ISBN = '"+QString::fromStdString(id)+"'"))
    {
        while (query.next())
            UserWhoBorrowedID = query.value(0).toString().toStdString();
    }

    if (UserWhoBorrowedID == this->user->getUserID())
    {
        ui->request->hide();
        ui->hold->hide();
        ui->renew->move(270, 310);
        ui->renew->show();
        ui->groupBox->hide();
        ui->label_6->setText("Already borrowed by you");
        return;
    }

    if (query.exec("Select borID from Borrow_Requests where ISBN = '"+QString::fromStdString(id)+"'"))
    {
        while (query.next())
            UserWhoBorrowedID = query.value(0).toString().toStdString();
    }

    if (UserWhoBorrowedID == this->user->getUserID())
    {
        ui->request->hide();
        ui->hold->hide();
        ui->groupBox->hide();
        ui->back->move(170, 310);
        ui->label_6->setText("Wait For Item Issuance");
        return;
    }

    bool holdCheck = false;
    if (query.exec("Select borID from Hold_Requests where ISBN = '"+QString::fromStdString(id)+"'"))
    {
        while (query.next())
        {
            UserWhoBorrowedID = query.value(0).toString().toStdString();
            if (UserWhoBorrowedID == this->user->getUserID())
            {
                holdCheck = true;
                break;
            }
        }
    }

    if (holdCheck == true)
    {
        ui->request->hide();
        ui->hold->hide();
        ui->groupBox->hide();
        ui->back->move(170, 310);
        ui->label_6->setText("You've already been put on hold");
        return;
    }

    if (borrower == true)
    {
        ui->request->hide();
        ui->hold->hide();
        ui->back->move(170,310);
        QSqlQuery query;
        if (query.exec ("Select borID from Loan_History where ISBN = '"+QString::fromStdString(id)+"'"))
        {
            while (query.next())
            {
                ui->listWidget->addItem(query.value(0).toString());
            }
        }
        if (subject == "Reference")
        {
            ui->groupBox->hide();
            ui->label_6->setText("No Loan History For Reference Books");
        }
        return;
    }

    if (subject == "Reference")
    {
        ui->hold->setEnabled(false);
        ui->request->setEnabled(false);
        ui->renew->setEnabled(false);
        ui->label_6->setText("Reference Book can't be borrowed");
        ui->groupBox->hide();
        return;
    }

    if (status)
    {
        ui->label_6->setText("Book already on Loan");
        ui->request->setEnabled(false);
    }
    else
    {
        ui->label_6->setText("Request a Clerk or Librarian");
        ui->hold->setEnabled(false);
    }

    ui->groupBox->hide();
}

ItemData::~ItemData()
{
    delete ui;
}

void ItemData::on_hold_clicked()
{
    lms->putItemOnHold(user, &obj);
    QSqlQuery query;
    query.exec("Insert into Hold_Requests (borID, ISBN) Values ('"+QString::fromStdString(user->getUserID())+"', "
               "'"+QString::fromStdString(obj.getItemID())+"')");
    ui->label_6->setText("You have been put on hold");
    ui->hold->setEnabled(false);
}

void ItemData::on_request_clicked()
{
    QSqlQuery query;
    query.exec("INSERT INTO Borrow_Requests (borID, ISBN) VALUES ('"+QString::fromStdString(user->getUserID())+"',  "
               "'"+QString::fromStdString(obj.getItemID())+"'); ");
    query.exec("UPDATE LibItems SET Loan = '"+QString::fromStdString("true")+"' "
              "WHERE ISBN = '"+QString::fromStdString(obj.getItemID())+"'");
    lms->setItemStatus(obj.getItemID());
    ui->request->setEnabled(false);
    ui->label_6->setText("Your Request has been recorded");
}

void ItemData::on_back_clicked()
{
    this->hide();
    delete ui;
}

void ItemData::on_renew_clicked()
{
    QSqlQuery query;
    string iDate, rDate;
    if (query.exec("Select IssueDate, ReturnDate from Items_Borrowed where borID = '"+QString::fromStdString(user->getUserID())+"'"
                "and ISBN = '"+QString::fromStdString(obj.getItemID())+"'"))
    {
        while (query.next())
        {
            iDate = query.value(0).toString().toStdString();
            rDate = query.value(1).toString().toStdString();
        }
    }
    query.exec("INSERT INTO Renew_Requests (borID, ISBN, IssueDate, ReturnDate) VALUES ('"+QString::fromStdString(user->getUserID())+"',  "
               "'"+QString::fromStdString(obj.getItemID())+"', '"+QString::fromStdString(iDate)+"', '"+QString::fromStdString(rDate)+"')");
    query.exec("UPDATE LibItems SET Loan = '"+QString::fromStdString("true")+"' "
              "WHERE ISBN = '"+QString::fromStdString(obj.getItemID())+"'");
    lms->setItemStatus(obj.getItemID());
    ui->label_6->setText("Your Renew Request is recorded");
    ui->renew->setEnabled(false);
}
