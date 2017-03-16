#include "renewitems.h"
#include "ui_renewitems.h"

RenewItems::RenewItems(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::RenewItems)
{
    ui->setupUi(this);
}

RenewItems::~RenewItems()
{
    delete ui;
}

void RenewItems::setValues(LMS* lms, string id, string name, string mob)
{
    obj.setUserID(id);
    obj.setUserName(name);
    obj.setMobileNumber(mob);
    obj.setLMSReference(lms);
    this->lms = lms;
}

void RenewItems::setTable()
{
    int count = 0;
    QStringList header;
    header << "Borrower ID" << "Book ISBN" << "Issue Date" << "Return Date";
    QSqlQuery query;
    if (query.exec("Select * from Renew_Requests"))
    {
        while (query.next())
            count++;
    }
    ui->fineSpin->setMinimum(50);
    ui->fineSpin->setMaximum(200);
    ui->daysSpin->setMinimum(1);
    ui->daysSpin->setMaximum(30);
    ui->tableWidget->setRowCount(count);
    ui->tableWidget->setColumnCount(4);
    ui->tableWidget->setHorizontalHeaderLabels(header);
    ui->tableWidget->setEditTriggers(QAbstractItemView::NoEditTriggers);
    if (ui->tableWidget->rowCount() == 0)
    {
        ui->renew->setEnabled(false);
        ui->calFine->setEnabled(false);
        return;
    }
    int i = 0;
    if (query.exec("Select * from Renew_Requests"))
    {
        while (query.next())
        {
            QTableWidgetItem* obj = new QTableWidgetItem(query.value(0).toString());
            obj->setTextAlignment(0x0080 | 0x0004);
            ui->tableWidget->setItem(i, 0, obj);
            obj = new QTableWidgetItem(query.value(1).toString());
            obj->setTextAlignment(0x0080 | 0x0004);
            ui->tableWidget->setItem(i, 1, obj);
            obj = new QTableWidgetItem(query.value(2).toString());
            obj->setTextAlignment(0x0080 | 0x0004);
            ui->tableWidget->setItem(i, 2, obj);
            obj = new QTableWidgetItem(query.value(3).toString());
            obj->setTextAlignment(0x0080 | 0x0004);
            ui->tableWidget->setItem(i, 3, obj);
            i++;
        }
    }

}

void RenewItems::fineCalculator()
{
    int row = ui->tableWidget->currentRow();
    int col = ui->tableWidget->currentColumn();
    if (col == 0)
    {
        borID = ui->tableWidget->item(row, col)->text().toStdString();
        bookID = ui->tableWidget->item(row, col+1)->text().toStdString();
        issueDate = ui->tableWidget->item(row, col+2)->text().toStdString();
        returnDate = ui->tableWidget->item(row, col+3)->text().toStdString();
    }
    else if (col == 1)
    {
        borID = ui->tableWidget->item(row, col-1)->text().toStdString();
        bookID = ui->tableWidget->item(row, col)->text().toStdString();
        issueDate = ui->tableWidget->item(row, col+1)->text().toStdString();
        returnDate = ui->tableWidget->item(row, col+2)->text().toStdString();
    }
    else if (col == 2)
    {
        borID = ui->tableWidget->item(row, col-2)->text().toStdString();
        bookID = ui->tableWidget->item(row, col-1)->text().toStdString();
        issueDate = ui->tableWidget->item(row, col)->text().toStdString();
        returnDate = ui->tableWidget->item(row, col+1)->text().toStdString();
    }
    else
    {
        borID = ui->tableWidget->item(row, col-3)->text().toStdString();
        bookID = ui->tableWidget->item(row, col-2)->text().toStdString();
        issueDate = ui->tableWidget->item(row, col-1)->text().toStdString();
        returnDate = ui->tableWidget->item(row, col)->text().toStdString();
    }

    QDateTime rDate = QDateTime::fromString(QString::fromStdString(returnDate));
    QDateTime cDate = QDateTime::currentDateTime();

    if (rDate.daysTo(cDate) < 0)
        ui->text->setText("No fine");
    else
    {
        int days = rDate.daysTo(cDate);
        double fine = days * ui->fineSpin->value();
        ui->text->setText(QString::number(fine));
        double prevFine = 0;
        QSqlQuery query;
        if (query.exec ("Select Fine from Borrowers where borID = '"+QString::fromStdString(borID)+"'")) {
            while (query.next())
                prevFine = query.value(0).toString().toDouble();
        }
        fine = fine + prevFine;
        string val = to_string(fine);
        query.exec("UPDATE Borrowers SET Fine = '"+QString::fromStdString(val)+"' "
                  "WHERE borID = '"+QString::fromStdString(borID)+"'");

        this->lms->setBorrowerFine(borID, fine);
    }
}

void RenewItems::on_back_clicked()
{
    this->hide();
    delete ui;
}

void RenewItems::on_renew_clicked()
{
    fineCalculator();
    QSqlQuery query;
    LibItem* l = this->lms->getItemFromID(bookID);
    User* u = this->lms->getUserFromID(borID);

    query.exec("Delete from Items_Borrowed where borID = '"+QString::fromStdString(borID)+"' "
                  "AND ISBN = '"+QString::fromStdString(bookID)+"'");

    obj.checkInItem(u, l);
    obj.checkOutItem(u, l);

    QDateTime issue_date = QDateTime::currentDateTime();
    string issueDate = issue_date.toString().toStdString();
    issue_date = issue_date.addDays(ui->daysSpin->value());
    string returnDate = issue_date.toString().toStdString();

    query.exec("Insert into Items_Borrowed (borID, ISBN, IssueDate, ReturnDate) Values ('"+QString::fromStdString(borID)+"', "
               "'"+QString::fromStdString(bookID)+"', '"+QString::fromStdString(issueDate)+"',"
                " '"+QString::fromStdString(returnDate)+"')");

    query.exec("Delete from Renew_Requests where borID = '"+QString::fromStdString(borID)+"' "
               "AND ISBN = '"+QString::fromStdString(bookID)+"'");

    query.exec("Insert into Loan_History (borID, ISBN) values ('"+QString::fromStdString(borID)+"', "
                "'"+QString::fromStdString(bookID)+"')");

    ui->text->setText("Item has been renewed");
    this->setTable();
}

void RenewItems::on_calFine_clicked()
{
    fineCalculator();
}
