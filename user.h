#pragma once
#include "LMS.h"
class Loan;
class LibItem;

class User
{
private:
    LMS* LMSobj;
    string user_ID;
    string name;
    string mobileNo;
    vector <Loan*> itemsBorrowed;
public:
    User ();
    User (string, string, string, LMS*);
    string getUserID ();
    string getUserName ();
    string getUserMobile ();
    LMS* getLMSReference ();
    vector <Loan*> getBorrowedItemsList ();
    void setLMSReference (LMS *);
    void setUserID (string);
    void setUserName (string);
    void setMobileNumber (string);
    void setBorrowedItems (vector <Loan*>);
    bool searchByTitle (string);
    bool searchByAuthor (string);
    bool searchBySubject (string);
    vector <string> getItemsFromTitle (string);
    vector <string> getItemsFromAuthor (string);
    vector <string> getItemsFromSubject (string);
    void putOnHold (LibItem *);
    void addLoan (Loan *);
    void removeLoan (Loan *);
    virtual void setFine (double) {}
    virtual double getFine () {return 0;}
    virtual void checkOutItem (User *, LibItem *, int) {}
    virtual void checkInItem (User *, LibItem *, double) {}
    virtual void renewItem (User *, LibItem *, int, double) {}
    virtual void addItem (LibItem *) {}
    virtual void delItem (LibItem *) {}
};

