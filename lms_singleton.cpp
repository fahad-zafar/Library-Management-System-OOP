#include "lms_singleton.h"

LMS* LMS_Singleton :: getMySystem()
{
    if (mySystem == nullptr)
        mySystem = new LMS;
    return mySystem;
}

LMS* LMS_Singleton :: mySystem = nullptr;
