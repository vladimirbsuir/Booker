#include "book.h"

Book::Book(int size) : Item(size) {}

QString Book::GetImage()
{
    return values[0];
}

QString Book::GetTitle()
{
    return values[1];
}

QString Book::GetDesc()
{
    return values[2];
}

QString Book::GetAuthor()
{
    return values[3];
}

QString Book::GetId()
{
    return values[4];
}

void Book::SetImage(QString data)
{
    values[0] = data;
}

void Book::SetTitle(QString data)
{
    values[1] = data;
}

void Book::SetDesc(QString data)
{
    values[2] = data;
}

void Book::SetAuthor(QString data)
{
    values[3] = data;
}

void Book::SetId(QString data)
{
    values[4] = data;
}
