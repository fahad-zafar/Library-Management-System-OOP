#include "Borrower.h"
#include "Loan.h"

Borrower :: Borrower () : User ()
{
    pendingFine = 0;
}

Borrower :: Borrower (string id, string name, string mob, double fine, LMS* lms) : User (id, name, mob, lms)
{
    pendingFine = fine;
}

void Borrower :: setFine (double fine)
{
    pendingFine = fine;
}

double Borrower :: getFine ()
{
    return pendingFine;
}
