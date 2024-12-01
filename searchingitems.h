#ifndef SEARCHINGITEMS_H
#define SEARCHINGITEMS_H

#include <QWidget>
#include <QGridLayout>
#include <QScrollArea>

class Item;
class MainWindow;

class SearchingItems : public QWidget
{
    Q_OBJECT
public:
    explicit SearchingItems(QWidget *parent = nullptr, MainWindow* mainWindow = nullptr);

    void SetItems(QVector<Item*>*);
    QScrollArea* GetArea();

private:
    MainWindow* mainWindow;

    QGridLayout* grid;
    QScrollArea* area;
};

#endif // SEARCHINGITEMS_H
