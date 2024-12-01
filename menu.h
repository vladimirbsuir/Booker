#ifndef MENU_H
#define MENU_H

#include <QWidget>
#include <QPushButton>
#include <QVBoxLayout>
#include <QLineEdit>
#include <QLabel>
#include <QMessageBox>
#include <QRadioButton>

//#include "mainwindow.h"
class Widget;
class Profile;
class BookPage;
class Database;
class User;
class Featured;
class SearchingItems;

class Menu : public QWidget
{
    Q_OBJECT
public:
    SearchingItems* GetSearchingWidget();

    void HideSearching();
    void ShowSearching();
    void HidePaging();
    void ShowPaging();

    explicit Menu(QWidget *parent = nullptr, Widget* catalog = nullptr, Profile* profile = nullptr, BookPage* page = nullptr, Database* database = nullptr, User* user = nullptr, Featured* featured = nullptr, SearchingItems* searching = nullptr);
private:
    Widget* catalog;
    Profile* profile;
    BookPage* page;
    Database* database;
    User* user;
    Featured* featured;
    SearchingItems* searching;

    QVBoxLayout* vbox;
    QVBoxLayout* vboxCatalog;
    QPushButton* profileBtn;
    QPushButton* featuredBtn;
    QPushButton* btn3;
    QPushButton* catalogBtn;
    QPushButton* quitBtn;
    QWidget* catalogAdd;

    QLineEdit* pageEnter;
    QLabel* pages;
    QPushButton* goToPage;

    QLabel* searchLabel;
    QLineEdit* searchEdit;
    QPushButton* searchBtn;
    QPushButton* returnBtn;
    QRadioButton* titleSearch;
    QRadioButton* authorSearch;
    QVBoxLayout* vboxSearch;
    QWidget* searchWidget;

public slots:
    void on_catBtn_clicked();
    void on_profileBtn_clicked();
    void on_catalogBtn_clicked();
    void on_featuredBtn_clicked();
    void on_quitBtn_clicked();
    void on_searchBtn_clicked();
    void on_titleSearch_toggled();
    void on_authorSearch_toggled();
    void on_returnBtn_clicked();
};

#endif // MENU_H
