#ifndef FEATURED_H
#define FEATURED_H

#include <QWidget>
#include <QScrollArea>
#include <QGridLayout>
#include <QVBoxLayout>
#include <QPixmap>

class Item;
class User;
class Widget;
class MainWindow;

class Featured : public QWidget
{
    Q_OBJECT
public:
    explicit Featured(QWidget *parent = nullptr, User* user = nullptr, Widget* catalog = nullptr, MainWindow* mainWindow = nullptr);

public:
    QScrollArea* GetArea();
    void SetBooks();

private:
    MainWindow* mainWindow;
    Widget* catalog;
    User* user;
    QStringList* featured;
    QVector<QString> images;
    QVector<QString> titles;

    QVector<Item*>* books;
    QVector<Item*>* sbooks;

    QScrollArea* area;
    QGridLayout* grid;
    QVBoxLayout* vbox;
    QWidget* widget;

    QVector<QWidget*>* widgets;
};

#endif // FEATURED_H
