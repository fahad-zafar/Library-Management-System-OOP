#include "checkoutitem.h"
#include "ui_checkoutitem.h"
using namespace std;
#include <iostream>

CheckOutItem::CheckOutItem(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::CheckOutItem)
{
    ui->setupUi(this);
    this->lms = lms;
}

CheckOutItem::~CheckOutItem()
{
    delete ui;
}

void CheckOutItem::setValues (LMS* lms, string id, string name, string mob)
{
    obj.setUserID(id);
    obj.setUserName(name);
    obj.setMobileNumber(mob);
    obj.setLMSReference(lms);

    this->lms = lms;
}

void CheckOutItem::on_back_clicked()
{
    this->hide();
    delete ui;
}

void CheckOutItem::setTable()
{
    int count = 0;
    QStringList header;
    header << "Borrower ID" << "Book ISBN";
    QSqlQuery query;

    if (query.exec("Select * from Borrow_Requests"))
    {
        while (query.next())
            count++;
    }
    ui->spinBox->setMinimum(1);
    ui->spinBox->setMaximum(30);
    ui->tableWidget->setRowCount(count);
    ui->tableWidget->setColumnCount(2);
    ui->tableWidget->setHorizontalHeaderLabels(header);
    ui->tableWidget->setEditTriggers(QAbstractItemView::NoEditTriggers);
    if (ui->tableWidget->rowCount() == 0)
    {
        ui->out->setEnabled(false);
        return;
    }
    int i = 0;
    if (query.exec("Select * from Borrow_Requests"))
    {
        while (query.next())
        {
            QTableWidgetItem* obj = new QTableWidgetItem(query.value(0).toString());
            obj->setTextAlignment(0x0080 | 0x0004);
            ui->tableWidget->setItem(i, 0, obj);
            obj = new QTableWidgetItem(query.value(1).toString());
            obj->setTextAlignment(0x0080 | 0x0004);
            ui->tableWidget->setItem(i, 1, obj);
            i++;
        }
    }
}

void CheckOutItem::on_out_clicked()
{
    string borID, bookID;
    int row = ui->tableWidget->currentRow();
    int col = ui->tableWidget->currentColumn();
    if (col == 1)
    {
        borID = ui->tableWidget->item(row, col-1)->text().toStdString();
        bookID = ui->tableWidget->item(row, col)->text().toStdString();
    }
    else
    {
        borID = ui->tableWidget->item(row, col)->text().toStdString();
        bookID = ui->tableWidget->item(row, col+1)->text().toStdString();
    }
    LibItem* l = this->lms->getItemFromID(bookID);
    User* u = this->lms->getUserFromID(borID);

    obj.checkOutItem(u, l);
    ui->text->setText("Item has been given on loan");
    this->lms->setItemStatus(bookID);

    QSqlQuery query;
    query.exec("Delete from Borrow_Requests where borID = '"+QString::fromStdString(borID)+"' "
                                "AND ISBN = '"+QString::fromStdString(bookID)+"'");

    QDateTime issue_date = QDateTime::currentDateTime();
    string issueDate = issue_date.toString().toStdString();
    issue_date = issue_date.addDays(ui->spinBox->value());
    string returnDate = issue_date.toString().toStdString();

    query.exec("Insert into Items_Borrowed (borID, ISBN, IssueDate, ReturnDate) Values ('"+QString::fromStdString(borID)+"', "
               "'"+QString::fromStdString(bookID)+"', '"+QString::fromStdString(issueDate)+"',"
                " '"+QString::fromStdString(returnDate)+"')");

    this->setTable();
}

