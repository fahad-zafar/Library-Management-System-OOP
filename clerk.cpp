#include "Clerk.h"
#include "Loan.h"

Clerk :: Clerk () : User () {}

Clerk :: Clerk (string id, string name, string mob, LMS* lms) : User (id, name, mob, lms) {}

void Clerk :: checkOutItem (User *u, LibItem *item)
{
    Loan *l = new Loan (u, item);
}

void Clerk :: checkInItem (User *u, LibItem *item)
{
    vector <Loan*> borrowedItems = u->getBorrowedItemsList ();
    for (int i = 0; i < borrowedItems.size(); i++)
    {
        if (borrowedItems.at(i)->getBorrowedItem() == item)
        {
            item->removeLoan (borrowedItems.at(i));
            u->removeLoan (borrowedItems.at(i));
            return;
        }
    }
}

void Clerk :: renewItem (User *u, LibItem *item)
{
    checkInItem (u, item);
    checkOutItem (u, item);
}
