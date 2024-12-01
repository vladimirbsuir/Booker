#ifndef OBASE_H
#define OBASE_H

#include <QSqlDatabase>
#include <QSqlQuery>

class OBase
{
public:
    OBase();

protected:
    QSqlDatabase db;
    QSqlQuery* query;
};

#endif // OBASE_H
