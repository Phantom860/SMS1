#ifndef BASE_H
#define BASE_H

#include "Affair.h"

class Base
{
public:
    Base();
    virtual ~Base() = 0;

    virtual bool selectAffair(QList<Affair> &scheduleList) = 0;
    virtual bool addAffair(Affair &schedule) = 0;
    virtual bool deleteAffair(int id) = 0;
    virtual bool updateAffair(Affair &schedule) = 0;

};

#endif // BASE_H
