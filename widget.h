#ifndef WIDGET_H
#define WIDGET_H

//#include "mylabel.h" ////////////////////
class MainWindow;
class MyLabel;
class Menu;
class Bookbase;
class Item;
class SBookbase;

#include <QWidget>
#include <QGridLayout>
#include <QPushButton>
#include <QScrollArea>
#include <QLabel>
#include <QPixmap>
#include <QFile>
#include <QString>
#include <QVector>
#include <QVBoxLayout>

class Widget : public QWidget
{
    Q_OBJECT
public:
    Widget(QWidget *parent = nullptr, MainWindow* wind = nullptr);
    ~Widget();
    QScrollArea* GetArea();
    QVector<QString>* GetTitlesV();
    QVector<QString>* GetImagesV();
    QVector<QString>* GetDescV();
    QVector<QString>* GetAuthorsV();
    void SetMainW(MainWindow* widget);
    void on_pageCatBtn_clicked(int);
    void ChangeBtns(int modifier, int firstN = 0);

    QVector<Item*>* GetBooks();
    QVector<Item*>* GetSBooks();

    QVector<QString> GetTitles();
    QVector<QString> GetImages();

    Bookbase* GetBookbase();
    SBookbase* GetSBookbase();

private:
    MainWindow* mainw;
    Bookbase* bookbase;
    SBookbase* sbookbase;

    QVector<Item*>* books;
    QVector<Item*>* sbooks;

    QString line;
    QByteArray rawLine;
    QVector<QString> images;
    QVector<QString> desc;
    QVector<QString> titles;
    QVector<QString> authors;
    QVector<QString> id;
    QGridLayout* grid;
    QVector<MyLabel*> myLabels;
    QVector<QLabel*> imageLabels;
    QVector<QPushButton*> btns;
    QVector<QVBoxLayout*> vboxes;
    QScrollArea* area;
    QPushButton* btn;
    QWidget* w2;
    QVBoxLayout* b;
    QLabel* lab;
    QVector<QPushButton*> pageBtns;
    QHBoxLayout* btnsLayout;

    int currentPage;
    int middlePage = 5;
public slots:
    void on_btn_clicked();
    void on_pageBtn_clicked();
};
#endif // WIDGET_H
