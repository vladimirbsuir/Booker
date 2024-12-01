#include "database.h"
#include "user.h"

#include <QSqlError>

Database::Database(User* user) : OBase() {
    this->user = user;

    db = QSqlDatabase::addDatabase("QSQLITE");
    db.setDatabaseName("./users.db");
    query = new QSqlQuery(db);
    db.open();

    query->exec("CREATE TABLE IF NOT EXISTS User(login TEXT, pass TEXT, image TEXT, featured TEXT);");
}

void Database::InsertUser(QString login, QString pass)
{
    query->prepare("INSERT INTO User(login, pass) VALUES(:login, :pass);");
    query->bindValue(":login", login);
    query->bindValue(":pass", pass);
    query->exec();
}

QVector<QString>* Database::GetUser(QString login, QString pass)
{
    query->prepare("SELECT login, pass FROM User WHERE login = :login AND pass = :pass");
    query->bindValue(":login", login);
    query->bindValue(":pass", pass);
    query->exec();
    query->first();

    qDebug() << query->value(0).toString() << " " << query->value(1).toString();;

    return new QVector<QString>;
}

bool Database::CheckUser(QString login, QString pass)
{
    query->prepare("SELECT login, pass FROM User WHERE login = :login AND pass = :pass");
    query->bindValue(":login", login);
    query->bindValue(":pass", pass);
    query->exec();

    if (!query->first()) return 0;

    return 1;
}

bool Database::UpdateUser(QString newInfo, int type)
{
    if (CheckUser(user->GetLogin(), user->GetPass()))
    {
        if (type == 0)
        {
            query->prepare("UPDATE User SET login = :newInfo WHERE login = :login");
            query->bindValue(":newInfo", newInfo);
            query->bindValue(":login", user->GetLogin());
            query->exec();

            user->SetLogin(newInfo);
        }
        else if (type == 1)
        {
            query->prepare("UPDATE User SET pass = :newInfo WHERE login = :login");
            query->bindValue(":newInfo", newInfo);
            query->bindValue(":login", user->GetLogin());
            query->exec();

            user->SetPass(newInfo);
        }
        else if (type == 2)
        {
            query->prepare("UPDATE User SET image = :newInfo WHERE login = :login");
            query->bindValue(":newInfo", newInfo);
            query->bindValue(":login", user->GetLogin());
            query->exec();

            user->SetImage(newInfo);
        }
        else if (type == 3)
        {
            query->prepare("UPDATE User SET featured = :newInfo WHERE login = :login");
            query->bindValue(":newInfo", newInfo);
            query->bindValue(":login", user->GetLogin());
            query->exec();
        }
    }
    else return 0;

    return 1;
}

QString Database::GetUserFeatured()
{
    query->prepare("SELECT featured FROM User WHERE login = :login");
    query->bindValue(":login", user->GetLogin());
    query->exec();
    query->first();

    qDebug() << query->value(0).toString();
    return query->value(0).toString();
}

QString Database::GetUserImage()
{
    query->prepare("SELECT image FROM User WHERE login = :login");
    query->bindValue(":login", user->GetLogin());
    query->exec();
    query->first();

    qDebug() << "aaa " << query->value(0).toString();
    return query->value(0).toString();
}
