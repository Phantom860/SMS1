#ifndef MYDATABASE_H
#define MYDATABASE_H

#include "Base.h"
#include "Affair.h"

#include <QSqlDatabase>

class MyDatabase : public Base
{
public:
    MyDatabase();

    ~ MyDatabase();


    virtual bool selectAffair(QList<Affair> &scheduleList) override;
    virtual bool addAffair(Affair &schedule) override;
    virtual bool updateAffair(Affair &schedule) override;
    virtual bool deleteAffair(int id) override;

private:
    QSqlDatabase m_db;
};

#endif // MYDATABASE_H
