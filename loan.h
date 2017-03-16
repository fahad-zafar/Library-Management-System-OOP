#pragma once
#include <ctime>
#include "User.h"
#include "LibItem.h"

class Loan
{
private:
    User* borrowedBy;
    LibItem* itemBorrowed;
public:
    Loan ();
    Loan (User*, LibItem*);
    LibItem* getBorrowedItem ();
    User* getUserWhoBorrowed ();
};

