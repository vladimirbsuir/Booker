#include "item.h"

Item::Item(int size) {
    this->size = size;
    values = new QString[size];
}

QString* Item::GetValues()
{
    return values;
}
