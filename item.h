#ifndef ITEM_H
#define ITEM_H

#include <QDebug>

class Item
{
public:
    virtual void Print()
    {
        qDebug() << "Print";
    }
    QString* GetValues();

    Item(int);

protected:
    QString* values;
    int size;
};

#endif // ITEM_H
