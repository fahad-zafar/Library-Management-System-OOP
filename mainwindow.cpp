#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <iostream>
using namespace std;

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    // setting connection with DataBase
    myDB = new QSqlDatabase (QSqlDatabase :: addDatabase ("QSQLITE"));
    myDB->setDatabaseName("E:/University/Semester 5/OOAD/Qt Projects/14-4048/Library.sqlite");

    if (myDB->open()) {
        ui->label->setText("Connected");
    }
    else
        ui->label->setText("Failed");
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::setUpLMSVectors(LMS* obj)
{
    this->obj = obj;

    // Filling up Users vector in LMS
    int index = 0, size = 0;
    QSqlQuery query;
    query.exec ("Select * from Borrowers");
    while (query.next())
    {
        size++;
    }
    Borrower* all_borrowers = new Borrower [size];
    query.exec ("Select * from Borrowers");
    while (query.next())
    {
        string id = query.value(0).toString().toStdString();
        string name = query.value(1).toString().toStdString();
        string mob = query.value(2).toString().toStdString();
        double fine = query.value(5).toString().toDouble();
        Borrower temp (id, name, mob, fine, this->obj);
        all_borrowers[index++] = temp;
    }

    for (int i = 0; i < size; i++)
        this->obj->addUser(&all_borrowers[i]);

    // Filling up LibItems Vector in LMS
    int count = 0;
    index = 0;
    query.exec ("Select * from LibItems");
    while (query.next())
    {
        count++;
    }
    query.exec ("Select * from LibItems");
    LibItem** all_items = new LibItem* [count];

    while (query.next())
    {
        string id = query.value(0).toString().toStdString();
        string title = query.value(1).toString().toStdString();
        string subject = query.value(2).toString().toStdString();
        string author = query.value(3).toString().toStdString();
        string loan = query.value(4).toString().toStdString();

        LibItem* temp = new LibItem ();
        temp->setItemID(id);
        temp->setItemTitle(title);
        temp->setItemSubject(subject);
        temp->setItemAuthor(author);
        temp->setItemReference(this->obj);

        if (loan == "true")
            temp->Handle();
        all_items[index++] = temp;
    }
    for (int i = 0; i < count; i++)
        this->obj->addItem(all_items[i]);

    query.exec("Select libFine from Librarians");
    while (query.next()) {
        double fine = query.value(0).toString().toDouble();
        this->obj->setFineCollected(fine);
    }
}

void MainWindow::on_signin_clicked()
{
    QString username, password;
    username = ui->lineEdit_username->text();
    password = ui->lineEdit_password->text();

    if (!myDB->isOpen()) {
        qDebug() << "Failed to open the DataBase";
        return;
    }

    bool check = false;
    QSqlQuery qry;
    if (qry.exec("select * from Borrowers where borUsername = '"+username+"' and borPassword = '"+password+"'"))
    {
        int count = 0;
        while (qry.next())
        {
            count++;
            if (count == 1) {
                this->hide();
                BorrowerData borrowerobj;
                QString id = qry.value(0).toString();
                QString name = qry.value(1).toString();
                QString mob = qry.value(2).toString();
                QString fine = qry.value(5).toString();
                vector <QString> books;
                QSqlQuery qry2;
                qry2.exec("select ISBN from Items_Borrowed where borID = '"+id+"'");
                while (qry2.next()) {
                    books.push_back(qry2.value(0).toString());
                }
                borrowerobj.setValues(id, name, mob, books, fine, this->obj, myDB);
                borrowerobj.exec();
                check = true;
                break;
            }
        }
        on_clear_clicked();
        this->show();
    }
    if (check == true)
        return;
    if (qry.exec("select * from Clerks where clerkUsername = '"+username+"' and clerkPassword = '"+password+"'"))
    {
        int count = 0;
        while (qry.next())
        {
            count++;
            if (count == 1) {
                this->hide();
                ClerkData clerkobj;
                QString id = qry.value(0).toString();
                QString name = qry.value(1).toString();
                QString mob = qry.value(2).toString();
                clerkobj.setValues(id, name, mob, this->obj);
                clerkobj.exec();
                check = true;
                break;
            }
        }
        on_clear_clicked();
        this->show();
    }
    if (check == true)
        return;
    if (qry.exec("select * from Librarians where libUsername = '"+username+"' and libPassword = '"+password+"'"))
    {
        int count = 0;
        while (qry.next())
        {
            count++;
            if (count == 1) {
                this->hide();
                LibrarianData libObj;
                QString id = qry.value(0).toString();
                QString name = qry.value(1).toString();
                QString mob = qry.value(2).toString();
                libObj.setValues(id, name, mob, this->obj);
                libObj.exec();
                check = true;
                break;
            }
        }
        on_clear_clicked();
        this->show();
    }
    if (check == false)
        ui->label->setText("Incorrect Username or Password");
}

void MainWindow::on_clear_clicked()
{
    ui->lineEdit_username->clear();
    ui->lineEdit_password->clear();
    ui->label->clear();
}
