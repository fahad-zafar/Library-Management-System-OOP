#pragma once
#include "User.h"
class Loan;

class Clerk : public User
{
private:

public:
    Clerk ();
    Clerk (string, string, string, LMS*);
    void checkOutItem (User *, LibItem *);
    void checkInItem (User *, LibItem *);
    void renewItem (User *, LibItem *);
};

