#include "clerkdata.h"
#include "ui_clerkdata.h"

ClerkData::ClerkData(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::ClerkData)
{
    ui->setupUi(this);
    ui->details->setEnabled(false);
}

ClerkData::~ClerkData()
{
    delete ui;
}

void ClerkData::setValues(QString id, QString name, QString mob, LMS *lms)
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

void ClerkData::on_ctitle_clicked()
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

void ClerkData::on_cauthor_clicked()
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

void ClerkData::on_csubject_clicked()
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

void ClerkData::on_signOut_clicked()
{
    this->hide();
    delete ui;
}

void ClerkData::on_pushButton_2_clicked()
{
    ChangeBorrowerInfo obj (this->lms);
    obj.exec();
}

void ClerkData::on_pushButton_clicked()
{
    AddBorrower obj(this->lms);
    obj.exec();
}

void ClerkData::on_pushButton_5_clicked()
{
    BorrowerInfo obj;
    obj.exec();
}

void ClerkData::on_pushButton_3_clicked()
{
    CheckOutItem obj;
    obj.setValues (this->obj.getLMSReference(), this->obj.getUserID(), this->obj.getUserName(), this->obj.getUserMobile());
    obj.setTable();
    obj.exec();
}

void ClerkData::on_pushButton_4_clicked()
{
    ReturnItem obj;
    obj.setValues(this->obj.getLMSReference(),this->obj.getUserID(), this->obj.getUserName(), this->obj.getUserMobile());
    obj.setTable();
    obj.exec();
}

void ClerkData::on_pushButton_7_clicked()
{
    HoldRequestsWindow obj;
    obj.setValues (this->obj.getLMSReference(), this->obj.getUserID(), this->obj.getUserName(), this->obj.getUserMobile());
    obj.setTable();
    obj.exec();
}

void ClerkData::itemClickedSlot (QListWidgetItem * itemClicked)
{
    ui->details->setEnabled(true);
}

void ClerkData::on_details_clicked()
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

void ClerkData::on_pushButton_6_clicked()
{
    RenewItems obj;
    obj.setValues (this->obj.getLMSReference(), this->obj.getUserID(), this->obj.getUserName(), this->obj.getUserMobile());
    obj.setTable();
    obj.exec();
}
