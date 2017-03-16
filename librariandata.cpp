#include "librariandata.h"
#include "ui_librariandata.h"

LibrarianData::LibrarianData(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::LibrarianData)
{
    ui->setupUi(this);
    ui->details->setEnabled(false);
    ui->flabel->hide();
    ui->fvalue->hide();
}

LibrarianData::~LibrarianData()
{
    delete ui;
}

void LibrarianData::setValues(QString id, QString name, QString mob, LMS *lms)
{
    this->lms = lms;
    ui->cID->setText(id);
    ui->cName->setText(name);
    ui->cMob->setText(mob);
    obj.setLMSReference(lms);
    obj.setUserID(id.toStdString());
    obj.setUserName(name.toStdString());
    obj.setMobileNumber(mob.toStdString());
}

void LibrarianData::on_addBor_clicked()
{
    AddBorrower obj (this->lms);
    obj.exec();
}

void LibrarianData::on_changeBo_clicked()
{
    ChangeBorrowerInfo obj (this->lms);
    obj.exec();
}

void LibrarianData::on_checkBor_clicked()
{
    BorrowerInfo obj;
    obj.exec();
}

void LibrarianData::on_checkIn_clicked()
{
    ReturnItem obj;
    obj.setValues(this->obj.getLMSReference(),this->obj.getUserID(), this->obj.getUserName(), this->obj.getUserMobile());
    obj.setTable();
    obj.exec();
}

void LibrarianData::on_checkOut_clicked()
{
    CheckOutItem obj;
    obj.setValues (this->obj.getLMSReference(), this->obj.getUserID(), this->obj.getUserName(), this->obj.getUserMobile());
    obj.setTable();
    obj.exec();
}

void LibrarianData::on_renew_clicked()
{
    RenewItems obj;
    obj.setValues (this->obj.getLMSReference(), this->obj.getUserID(), this->obj.getUserName(), this->obj.getUserMobile());
    obj.setTable();
    obj.exec();
}

void LibrarianData::on_holdReq_clicked()
{
    HoldRequestsWindow obj;
    obj.setValues (this->obj.getLMSReference(), this->obj.getUserID(), this->obj.getUserName(), this->obj.getUserMobile());
    obj.setTable();
    obj.exec();
}

void LibrarianData::on_addItem_clicked()
{
    AddItem obj (this->lms);
    obj.exec();
}

void LibrarianData::on_changeItem_clicked()
{
    ChangeItemInfo obj (this->lms);
    obj.exec();
}

void LibrarianData::on_delItem_clicked()
{
    DelItem obj (this->lms);
    obj.exec();
}

void LibrarianData::on_ctitle_clicked()
{
    ui->clistWidget_2->clear();
    ui->cauthor_2->clear();
    ui->csubject_2->clear();
    string input = ui->ctitle_2->text().toStdString();
    bool val = obj.searchByTitle(input);
    if (val) {
        ui->clabel_6->setText("Book(s) Found");
        vector <string> items = obj.getItemsFromTitle(input);
        for (int i = 0; i < items.size(); i++)
            ui->clistWidget_2->addItem(QString::fromStdString(items.at(i)));
        connect(ui->clistWidget_2, SIGNAL(itemClicked(QListWidgetItem *)), this, SLOT(itemClickedSlot(QListWidgetItem *)));
    }
    else
        ui->clabel_6->setText("No Book Found");
}

void LibrarianData::on_cauthor_clicked()
{
    ui->ctitle_2->clear();
    ui->csubject_2->clear();
    ui->clistWidget_2->clear();
    string input = ui->cauthor_2->text().toStdString();
    bool val = obj.searchByAuthor(input);
    if (val) {
        ui->clabel_6->setText("Book(s) Found");
        vector <string> items = obj.getItemsFromAuthor(input);
        for (int i = 0; i < items.size(); i++)
            ui->clistWidget_2->addItem(QString::fromStdString(items.at(i)));
        connect(ui->clistWidget_2, SIGNAL(itemClicked(QListWidgetItem *)), this, SLOT(itemClickedSlot(QListWidgetItem *)));
    }
    else
        ui->clabel_6->setText("No Book Found");
}

void LibrarianData::on_csubject_clicked()
{
    ui->ctitle_2->clear();
    ui->cauthor_2->clear();
    ui->clistWidget_2->clear();
    string input = ui->csubject_2->text().toStdString();
    bool val = obj.searchBySubject(input);
    if (val) {
        ui->clabel_6->setText("Book(s) Found");
        vector <string> items = obj.getItemsFromSubject(input);
        for (int i = 0; i < items.size(); i++)
            ui->clistWidget_2->addItem(QString::fromStdString(items.at(i)));
        connect(ui->clistWidget_2, SIGNAL(itemClicked(QListWidgetItem *)), this, SLOT(itemClickedSlot(QListWidgetItem *)));
    }
    else
        ui->clabel_6->setText("No Book Found");
}

void LibrarianData::itemClickedSlot (QListWidgetItem * itemClicked)
{
    ui->details->setEnabled(true);
}

void LibrarianData::on_signOut_clicked()
{
    this->hide();
    delete ui;
}

void LibrarianData::on_details_clicked()
{
    ui->details->setEnabled(false);
    string title = ui->clistWidget_2->currentItem()->text().toStdString();
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
    itemobj.setValues(&obj, temp->getItemID(), temp->getItemTitle(), temp->getItemSubject(), temp->getItemAuthor(), val, this->lms, true);
    itemobj.exec();
}

void LibrarianData::on_totalFine_clicked()
{
    double fine = this->lms->getCollectedFine();
    ui->flabel->show();
    ui->fvalue->show();
    ui->fvalue->setText(QString::number(fine));
}
