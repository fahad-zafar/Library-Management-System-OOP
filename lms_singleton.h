#ifndef LMS_SINGLETON_H
#define LMS_SINGLETON_H
#include "LMS.h"

class LMS_Singleton
{
private:
    static LMS* mySystem;
public:
    static LMS* getMySystem();
};

#endif
