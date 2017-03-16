#include "onloan.h"
#include "available.h"

OnLoan::OnLoan(LibItem* b)
{
    _context = b;
}

ItemState* OnLoan :: Instance (LibItem* b)
{
    if (currState == nullptr)
        currState = new OnLoan (b);
    return currState;
}

void OnLoan::Handle()
{
    _context->setState(Available :: Instance(_context));
}

ItemState* OnLoan :: currState = nullptr;
