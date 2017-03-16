#pragma once
#include "LibItem.h"
#include "bookstate.h"

class Book : public LibItem
{

public:
    Book ();
    Book (string, string, string, string, LMS*);
};
