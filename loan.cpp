#include "Loan.h"

Loan :: Loan ()
{
    this->borrowedBy = nullptr;
    this->itemBorrowed = nullptr;
}

Loan :: Loan (User* u, LibItem* i)
{
    this->borrowedBy = u;
    this->itemBorrowed = i;
    u->addLoan (this);
    i->addLoan (this);
}

LibItem* Loan :: getBorrowedItem ()
{
    return itemBorrowed;
}

User* Loan :: getUserWhoBorrowed ()
{
    return borrowedBy;
}
