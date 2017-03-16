#include "available.h"
#include "onloan.h"

Available::Available(LibItem* b)
{
    _context = b;
}

ItemState* Available :: Instance (LibItem *b)
{
    if (currState == nullptr)
        currState = new Available (b);
    return currState;
}

void Available::Handle()
{
    _context->setState(OnLoan :: Instance(_context));
}

ItemState* Available :: currState = nullptr;
