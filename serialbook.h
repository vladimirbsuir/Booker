#ifndef SERIALBOOK_H
#define SERIALBOOK_H

#include "book.h"

class SerialBook : public Book
{
public:
    SerialBook();
    SerialBook(int);
    QVector<int>* GetIds();

private:
    QVector<int>* ids;
};

#endif // SERIALBOOK_H
