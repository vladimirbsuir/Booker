#ifndef BOOKPAGE_H
#define BOOKPAGE_H

#include <QWidget>
#include <QVBoxLayout>
#include <QScrollArea>
#include <QHBoxLayout>
#include <QLabel>
#include <QPushButton>

// Добавить добавление при авторизации featured строки с индексами книг, продумать, надо ли хранить в user эту строку, как обращаться к ней
// и выводить информацию

class Widget;
class MyImageLabel;
class User;

class BookPage : public QWidget
{
    Q_OBJECT

public:
    explicit BookPage(QWidget *parent = nullptr, Widget* catal = nullptr, User* user = nullptr);
    QLabel* GetTitle();
    QLabel* GetImage();
    QLabel* GetDesc();
    MyImageLabel* GetFeatureImage();
    int GetState();
    void SetIndex(int);
    void SetState(int);
    void ChangeFeatureImage();

public slots:
    void on_btn_clicked();

private:
    Widget* catal;
    User* user;

    QHBoxLayout* hbox;
    QVBoxLayout* vbox1;
    QVBoxLayout* vbox2;
    QScrollArea* area;
    QLabel* title;
    QLabel* image;
    QLabel* desc;
    QPushButton* btn;
    MyImageLabel* featureImage;
    int state;
    int index;

public:
    static QString addImagePath;
    static QString addedImagePath;
};

#endif // BOOKPAGE_H
