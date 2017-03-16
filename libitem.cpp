#include "LibItem.h"
#include "LMS.h"
#include "onloan.h"
#include "available.h"

LibItem :: LibItem ()
{
    this->LMSobj = new LMS ();
    this->item_ID = "";
    this->title = "";
    this->subject = "";
    this->author = "";
    this->LMSobj = new LMS ();
    _state = Available :: Instance(this);
}

LibItem :: LibItem (string id, string title, string subject, string author, LMS * obj)
{
    this->LMSobj = new LMS ();
    this->item_ID = id;
    this->title = title;
    this->subject = subject;
    this->author = author;
    this->LMSobj = obj;
}

void LibItem :: setState (ItemState *state)
{
    _state = state;
}

bool LibItem :: getState ()
{
    if (_state == OnLoan :: Instance(this))
        return true;
    else
        return false;
}

void LibItem :: setItemStatus ()
{
    this->Handle();
}

void LibItem :: Handle ()
{
    _state->Handle();
}

string LibItem :: getItemID ()
{
    return item_ID;
}

string LibItem :: getItemTitle ()
{
    return title;
}

string LibItem :: getItemSubject ()
{
    return subject;
}

string LibItem :: getItemAuthor ()
{
    return author;
}

Loan* LibItem :: getCurrentLoan ()
{
    return currLoan;
}

vector <User *> LibItem :: getHoldRequests ()
{
    return holdRequest;
}

void LibItem :: setHoldRequests (vector <User *> users)
{
    holdRequest = users;
}

void LibItem :: setItemID (string id)
{
    item_ID = id;
}

void LibItem :: setItemTitle (string title)
{
    this->title = title;
}

void LibItem :: setItemSubject (string subject)
{
    this->subject = subject;
}

void LibItem :: setItemAuthor (string author)
{
    this->author = author;
}

void LibItem :: setItemReference (LMS * obj)
{
    LMSobj = obj;
}

void LibItem :: clearAllLoans ()
{
    borrowingHistory.erase(borrowingHistory.begin(), borrowingHistory.begin() + borrowingHistory.size());
}

void LibItem :: addLoan (Loan *l)
{
    currLoan = l;
    borrowingHistory.push_back (l);
}

void LibItem :: removeLoan (Loan *l)
{
    currLoan = nullptr;
}

void LibItem :: setBorrowRequest (User *u)
{
    borrowRequest = u;
}
