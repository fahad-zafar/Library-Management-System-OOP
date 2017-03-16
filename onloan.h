#pragma once
#include "ItemState.h"
#include "libitem.h"

class OnLoan: public ItemState
{
private:
    static ItemState* currState;
    LibItem* _context;
public:
    OnLoan(LibItem* context);
    static ItemState* Instance (LibItem*);
    void Handle();
};
