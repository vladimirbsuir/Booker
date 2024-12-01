#include "serialbook.h"

SerialBook::SerialBook(int size) : Book(size) {
    ids = new QVector<int>;
}

QVector<int>* SerialBook::GetIds()
{
    return ids;
}
