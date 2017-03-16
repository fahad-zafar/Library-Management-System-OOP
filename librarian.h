#pragma once
#include "User.h"
class LibItem;

class Librarian : public User
{
public:
    Librarian ();
    Librarian (string, string, string, LMS*);
    void addItem (LibItem *);
    void delItem (LibItem *);
};

