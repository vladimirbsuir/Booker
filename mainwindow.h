#ifndef MAINWINDOW_H
#define MAINWINDOW_H

//#include "widget.h"
#include "bookpage.h"
#include "menu.h"
#include "regauthpage.h"

class Widget;
class User;
class Profile;
class Featured;

class MainWindow : public QWidget
{
    Q_OBJECT

public:
    void SetBookPage(int index);

public:
    explicit MainWindow(QWidget *parent = nullptr);

protected:
    virtual void closeEvent(QCloseEvent* event) Q_DECL_OVERRIDE;

private:
    Widget* catalog;
    RegAuthPage* regAuth;
    Menu* menu;
    BookPage* page;
    QHBoxLayout* hbox;
    Database* database;
    User* user;
    Profile* profile;
    Featured* featured;
};

#endif // MAINWINDOW_H
