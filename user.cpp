#include "user.h"

User::User() {
    featured = nullptr;
}

QString User::GetLogin()
{
    return login;
}

QString User::GetPass()
{
    return pass;
}

QString User::GetImage()
{
    return image;
}

QStringList* User::GetFeatured()
{
    return featured;
}

void User::SetLogin(QString login)
{
    this->login = login;
}

void User::SetPass(QString pass)
{
    this->pass = pass;
}

void User::SetImage(QString image)
{
    this->image = image;
}

void User::SetFeatured(QStringList* featured)
{
    this->featured = featured;
}
