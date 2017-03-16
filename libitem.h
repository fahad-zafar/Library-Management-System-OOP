#pragma once
#include "LMS.h"
#include "Loan.h"
#include "itemstate.h"

class LibItem
{
private:
    ItemState* _state;
    LMS* LMSobj;
    Loan* currLoan;
    vector <Loan *> borrowingHistory;
    User* borrowRequest;
    vector <User *> holdRequest;
    string item_ID;
    string title;
    string subject;
    string author;
public:
    void setState ( ItemState* state );
    void Handle();
    bool getState ();
    void setItemStatus ();
    LibItem ();
    LibItem (string, string, string, string, LMS*);
    string getItemID ();
    string getItemTitle ();
    string getItemSubject ();
    string getItemAuthor ();
    Loan* getCurrentLoan ();
    vector <User *> getHoldRequests ();
    void setHoldRequests (vector <User *>);
    void setItemID (string);
    void setItemTitle (string);
    void setItemSubject (string);
    void setItemAuthor (string);
    void setItemReference (LMS *);
    void setBorrowRequest (User *);
    void clearAllLoans ();
    void addLoan (Loan *);
    void removeLoan (Loan *);
};

