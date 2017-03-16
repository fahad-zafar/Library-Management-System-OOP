#pragma once
#include "User.h"
class Loan;

class Borrower : public User
{
private:
    double pendingFine;
public:
    Borrower ();
    Borrower (string, string, string, double, LMS*);
    void setFine (double);
    double getFine ();
};
