#include "User.h"
#include "LibItem.h"
#include "Loan.h"

User :: User ()
{
    this->user_ID = "";
    this->name = "";
    this->mobileNo = "";
    LMSobj = nullptr;
}

User :: User (string id, string name, string mob, LMS* lms)
{
    this->user_ID = id;
    this->name = name;
    this->mobileNo = mob;
    LMSobj = lms;
}

string User :: getUserID ()
{
    return user_ID;
}

string User :: getUserName ()
{
    return name;
}

string User :: getUserMobile ()
{
    return mobileNo;
}

LMS* User :: getLMSReference ()
{
    return LMSobj;
}

vector <Loan*> User :: getBorrowedItemsList ()
{
    return itemsBorrowed;
}

void User :: setLMSReference (LMS* lms)
{
    LMSobj = lms;
}

void User :: setUserID (string id)
{
    user_ID = id;
}

void User :: setUserName (string name)
{
    this->name = name;
}

void User :: setMobileNumber (string mob)
{
    mobileNo = mob;
}

void User :: setBorrowedItems (vector <Loan*> l)
{
    itemsBorrowed = l;
}

bool User :: searchByTitle (string title)
{
    return LMSobj->searchByTitle (title);
}

bool User :: searchByAuthor (string author)
{
    return LMSobj->searchByAuthor (author);
}

bool User :: searchBySubject (string subject)
{
   return LMSobj->searchBySubject (subject);
}

vector <string> User :: getItemsFromTitle (string title)
{
    return LMSobj->getItemsFromTitle (title);
}

vector <string> User :: getItemsFromAuthor (string author)
{
    return LMSobj->getItemsFromAuthor (author);
}

vector <string> User :: getItemsFromSubject (string subject)
{
    return LMSobj->getItemsFromSubject (subject);
}

void User :: putOnHold (LibItem *item)
{
    LMSobj->putItemOnHold (this, item);
}

void User :: addLoan (Loan *l)
{
    itemsBorrowed.push_back (l);
}

void User :: removeLoan (Loan *l)
{
    for (int i = 0; i < itemsBorrowed.size(); i++)
    {
        if (itemsBorrowed.at(i) == l)
        {
            itemsBorrowed.erase(itemsBorrowed.begin()+i);
            break;
        }
    }
}
