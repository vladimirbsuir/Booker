#ifndef DATABASE_H
#define DATABASE_H

#include "obase.h"

class User;

class Database : public OBase
{
public:
    Database(User* user = nullptr);

    void InsertUser(QString, QString);
    QVector<QString>* GetUser(QString, QString);
    bool CheckUser(QString, QString);
    bool UpdateUser(QString, int);
    QString GetUserImage();
    QString GetUserFeatured();

private:
    User* user;

    //QSqlDatabase db;
    //QSqlQuery* query;
};

#endif // DATABASE_H
