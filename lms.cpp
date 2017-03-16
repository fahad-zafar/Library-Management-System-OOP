#include "LMS.h"
#include "LibItem.h"
#include "User.h"

LMS :: LMS ()
{
    fineCollected = 0;
}

double LMS :: getCollectedFine ()
{
    return fineCollected;
}

void LMS :: setFineCollected(double fine)
{
    fineCollected = fineCollected + fine;
}

vector <User *> LMS :: getAllUsers ()
{
    return all_users;
}

vector <LibItem *> LMS :: getAllItems ()
{
    return all_items;
}

bool LMS :: searchByTitle (string title)
{
    for (int i = 0; i < all_items.size(); i++)
    {
        if (all_items[i]->getItemTitle() == title)
            return true;
    }
    return false;
}

bool LMS ::	searchByAuthor (string author)
{
    for (int i = 0; i < all_items.size(); i++)
    {
        if (all_items[i]->getItemAuthor() == author)
            return true;
    }
    return false;
}

bool LMS :: searchBySubject (string subject)
{
    for (int i = 0; i < all_items.size(); i++)
    {
        if (all_items[i]->getItemSubject() == subject)
            return true;
    }
    return false;
}

void LMS :: setItemStatus (string id)
{
    for (int i = 0; i < all_items.size(); i++)
    {
        if (all_items[i]->getItemID() == id)
        {
            all_items.at(i)->setItemStatus();
            return;
        }
    }
}

vector <string> LMS :: getItemsFromTitle (string title)
{
    vector <string> matchedBooks;
    for (int i = 0; i < all_items.size(); i++)
    {
        if (all_items[i]->getItemTitle() == title)
            matchedBooks.push_back(all_items[i]->getItemTitle());
    }
    return matchedBooks;
}

vector <string> LMS :: getItemsFromAuthor (string author)
{
    vector <string> matchedBooks;
    for (int i = 0; i < all_items.size(); i++)
    {
        if (all_items[i]->getItemAuthor() == author)
            matchedBooks.push_back(all_items[i]->getItemTitle());
    }
    return matchedBooks;
}

vector <string> LMS :: getItemsFromSubject (string subject)
{
    vector <string> matchedBooks;
    for (int i = 0; i < all_items.size(); i++)
    {
        if (all_items[i]->getItemSubject() == subject)
            matchedBooks.push_back(all_items[i]->getItemTitle());
    }
    return matchedBooks;
}

User* LMS :: getUserFromID (string id)
{
    for (int i = 0; i < all_users.size(); i++)
    {
        if (all_users[i]->getUserID() == id)
            return all_users[i];
    }
}

LibItem* LMS :: getItemFromID (string id)
{
    for (int i = 0; i < all_items.size(); i++)
    {
        if (all_items[i]->getItemID() == id)
            return all_items[i];
    }
}

LibItem* LMS :: getItem(string title)
{
    for (int i = 0; i < all_items.size(); i++)
    {
        if (all_items[i]->getItemTitle() == title)
            return all_items[i];
    }
}

void LMS :: setBorrowerFine (string id, double fine)
{
    for (int i = 0; i < all_users.size(); i++)
    {
        if (all_users[i]->getUserID() == id)
        {
            all_users[i]->setFine (fine);
            return;
        }
    }
}

void LMS :: addItem (LibItem *item)
{
    all_items.push_back (item);
}

void LMS :: addUser (User *user)
{
    all_users.push_back (user);
}

void LMS :: delItem (LibItem *item)
{
    for (int i = 0; i < all_items.size(); i++)
    {
        if (all_items[i]->getItemID() == item->getItemID())
        {
            all_items[i]->clearAllLoans();
            all_items.erase(all_items.begin()+i);
        }
    }
    for (int i = 0; i < all_users.size(); i++)
    {
        vector <Loan*> loans = all_users[i]->getBorrowedItemsList();
        for (int j = 0; j < loans.size(); j++)
        {
            if (loans[i]->getBorrowedItem () == item)
                loans.erase(loans.begin()+j);
        }
        all_users[i]->setBorrowedItems (loans);
    }
}

void LMS :: changeInfo (string prevID, string id, string t, string s, string a)
{
    for (int i = 0; i < all_items.size(); i++)
    {
        if (all_items[i]->getItemID() == prevID)
        {
            all_items[i]->setItemID(id);
            all_items[i]->setItemTitle(t);
            all_items[i]->setItemSubject(s);
            all_items[i]->setItemAuthor(a);
            return;
        }
    }
}

void LMS :: changeUserInfo (string id, string mob)
{
    for (int i = 0; i < all_users.size(); i++)
    {
        if (all_users[i]->getUserID() == id)
        {
            all_users[i]->setMobileNumber(mob);
            return;
        }
    }
}

void LMS :: putItemOnHold (User *u, LibItem *item)
{
    item->setBorrowRequest (u);
}
