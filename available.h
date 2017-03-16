#pragma once
#include "ItemState.h"
#include "Book.h"

class Available: public ItemState
{
private:
    static ItemState* currState;
    LibItem* _context;
public:
    Available(LibItem *context);
    static ItemState* Instance (LibItem*);
    void Handle();
};
