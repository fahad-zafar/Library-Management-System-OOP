#include "Librarian.h"
#include "LibItem.h"

Librarian :: Librarian () : User () {}

Librarian :: Librarian (string id, string name, string mob, LMS* lms) : User (id, name, mob, lms) {}

void Librarian :: addItem (LibItem *item)
{
    LMS* temp = getLMSReference ();
    temp->addItem (item);
    setLMSReference (temp);
}

void Librarian :: delItem (LibItem *item )
{
    LMS* temp = getLMSReference ();
    Loan* borrowedBy = item->getCurrentLoan();
    vector <User*> userList = temp->getAllUsers ();
    bool check = false;

    for (int i = 0; i < userList.size(); i++)
    {
        vector <Loan*> eachUserLoanList = userList.at(i)->getBorrowedItemsList();
        for (int j = 0; j < eachUserLoanList.size(); j++)
        {
            if (eachUserLoanList.at(i) == borrowedBy)
            {
                userList.at(i)->removeLoan (borrowedBy);
                check = true;
                break;
            }
        }
        if (check = true)
            break;
    }

    item->removeLoan (borrowedBy);
    item->clearAllLoans ();
    temp->delItem (item);
    setLMSReference (temp);
}

