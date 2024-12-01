#include "menu.h"
#include "widget.h"
#include "profile.h"
#include "bookpage.h"
#include "database.h"
#include "user.h"
#include "featured.h"
#include "bookbase.h"
#include "sbookbase.h"
#include "searchingitems.h"

#include <QMessageBox>

#define btnH 100

Menu::Menu(QWidget *parent, Widget* catalog, Profile* profile, BookPage* page, Database* database, User* user, Featured* featured, SearchingItems* searching)
    : QWidget{parent}
{
    this->featured = featured;
    this->catalog = catalog;
    this->profile = profile;
    this->page = page;
    this->database = database;
    this->user = user;
    this->searching = searching;

    vbox = new QVBoxLayout();
    profileBtn = new QPushButton("Profile");
    featuredBtn = new QPushButton("Featured");
    btn3 = new QPushButton("Bucket");
    catalogBtn = new QPushButton("Catalog");
    quitBtn = new QPushButton("Quit");
    catalogAdd = new QWidget();
    goToPage = new QPushButton("Go to page");
    pages = new QLabel("Enter page (1-50): ");
    pageEnter = new QLineEdit();
    vboxCatalog = new QVBoxLayout();

    searchLabel = new QLabel("Enter title:");
    searchEdit = new QLineEdit();
    searchBtn = new QPushButton("Search");
    returnBtn = new QPushButton("Return");
    titleSearch = new QRadioButton("Title");
    authorSearch = new QRadioButton("Author");
    vboxSearch = new QVBoxLayout();
    searchWidget = new QWidget();

    titleSearch->setChecked(true);

    connect(goToPage, SIGNAL(clicked()), SLOT(on_catBtn_clicked()));

    this->setFixedWidth(150);
    profileBtn->setMinimumHeight(btnH);
    featuredBtn->setMinimumHeight(btnH);
    btn3->setMinimumHeight(btnH);
    catalogBtn->setMinimumHeight(btnH);
    vbox->addWidget(profileBtn);
    vbox->addWidget(featuredBtn);
    vbox->addWidget(btn3);
    vbox->addWidget(catalogBtn);

    vbox->addStretch(0);

    catalogAdd->setLayout(vboxCatalog);
    vbox->addWidget(catalogAdd);

    vbox->addStretch(0);

    vboxCatalog->addWidget(pages);
    vboxCatalog->addWidget(pageEnter);
    vboxCatalog->addWidget(goToPage);

    vboxSearch->addWidget(titleSearch);
    vboxSearch->addWidget(authorSearch);
    vboxSearch->addWidget(searchLabel);
    vboxSearch->addWidget(searchEdit);
    vboxSearch->addWidget(searchBtn);
    vboxSearch->addWidget(returnBtn);

    searchWidget->setLayout(vboxSearch);
    vbox->addWidget(searchWidget);

    vbox->addStretch(0);

    vbox->addWidget(quitBtn);

    //vbox->addStretch(0);
    vbox->setContentsMargins(0,0,0,0);

    this->setLayout(vbox);

    connect(profileBtn, SIGNAL(clicked()), SLOT(on_profileBtn_clicked()));
    connect(catalogBtn, SIGNAL(clicked()), SLOT(on_catalogBtn_clicked()));
    connect(quitBtn, SIGNAL(clicked()), SLOT(on_quitBtn_clicked()));
    connect(featuredBtn, SIGNAL(clicked()), SLOT(on_featuredBtn_clicked()));
    connect(searchBtn, SIGNAL(clicked()), SLOT(on_searchBtn_clicked()));
    connect(titleSearch, SIGNAL(clicked()), SLOT(on_titleSearch_toggled()));
    connect(authorSearch, SIGNAL(clicked()), SLOT(on_authorSearch_toggled()));
    connect(returnBtn, SIGNAL(clicked()), SLOT(on_returnBtn_clicked()));
}

void Menu::on_quitBtn_clicked()
{
    QMessageBox::StandardButton answer = QMessageBox::question(this, "Question", "Do you really want to quit?", QMessageBox::Yes | QMessageBox::No);
    if (answer == QMessageBox::Yes)
    {
        database->UpdateUser(user->GetFeatured()->join(" "), 3);
        exit(0);
    }
}

void Menu::on_catBtn_clicked()
{
    QString page = pageEnter->text();

    if (page.size() == 0)
    {
        QMessageBox::about(this, "Warning", "Enter page number");
        return;
    }
    if (page[0] == '0')
    {
        QMessageBox::about(this, "Warning", "Enter correct page number");
        return;
    }
    for (int i = 0; i < page.size(); i++)
    {
        if (!page[i].isDigit())
        {
            QMessageBox::about(this, "Warning", "Enter only numbers");
            return;
        }
    }

    catalog->on_pageCatBtn_clicked(page.toInt());
}

void Menu::on_profileBtn_clicked()
{
    if (profile->isHidden())
    {
        if (!catalog->GetArea()->isHidden())
        {
            HidePaging();
            HideSearching();

            catalog->GetArea()->hide();
        }
        if (!page->isHidden()) page->hide();
        if (!featured->GetArea()->isHidden()) featured->GetArea()->hide();
        if (!searching->GetArea()->isHidden()) searching->GetArea()->hide();

        if (user->GetLogin() == aLogin && user->GetPass() == aPass)
        {
            //profile->GetUpdateItemBtn()->show();
            //profile->GetAddItemBtn()->show();
            profile->ShowABtns();
        }
        profile->show();
    }
}

void Menu::on_catalogBtn_clicked()
{
    if (catalog->GetArea()->isHidden())
    {
        if (!profile->isHidden())
        {
            //profile->GetAddItemBtn()->hide();
            profile->hide();
        }
        if (!page->isHidden()) page->hide();
        if (!featured->GetArea()->isHidden()) featured->GetArea()->hide();
        if (!searching->GetArea()->isHidden()) searching->GetArea()->hide();

        ShowPaging();
        ShowSearching();

        catalog->GetArea()->show();
    }
}

void Menu::on_featuredBtn_clicked()
{
    if (featured->GetArea()->isHidden())
    {
        if (!profile->isHidden())
        {
            //profile->GetAddItemBtn()->hide();
            profile->hide();
        }
        if (!page->isHidden()) page->hide();
        if (!searching->GetArea()->isHidden()) searching->GetArea()->hide();
        if (!catalog->GetArea()->isHidden())
        {
            HidePaging();
            HideSearching();

            catalog->GetArea()->hide();
        }

        featured->SetBooks();
        featured->GetArea()->show();
    }
}

void Menu::on_searchBtn_clicked()
{
    int type = 0;

    if (searchEdit->text() == "")
    {
        QMessageBox::warning(this, "Warning", "Fill search field");
        return;
    }

    if (titleSearch->isChecked()) type = 2;
    else if (authorSearch->isChecked()) type = 3;

    QVector<Item*>* books = catalog->GetBookbase()->Search(searchEdit->text(), type);
    QVector<Item*>* sbooks = catalog->GetSBookbase()->Search(searchEdit->text(), type);
    QVector<Item*>* items = new QVector<Item*>();
    if (sbooks != nullptr) items->append(*sbooks);
    if (books != nullptr) items->append(*books);

    catalog->GetArea()->hide();
    this->HidePaging();
    searching->SetItems(items);
}

void Menu::on_returnBtn_clicked()
{
    if (!searching->GetArea()->isHidden())
    {
        searching->GetArea()->hide();
        catalog->GetArea()->show();
        this->ShowPaging();
        searchEdit->clear();
    }
}

void Menu::on_titleSearch_toggled()
{
    searchLabel->setText("Enter title:");
}

void Menu::on_authorSearch_toggled()
{
    searchLabel->setText("Enter author:");
}

void Menu::HideSearching()
{
    searchLabel->hide();
    searchEdit->hide();
    titleSearch->hide();
    authorSearch->hide();
    searchBtn->hide();
    returnBtn->hide();
}

void Menu::ShowSearching()
{
    searchLabel->show();
    searchEdit->show();
    titleSearch->show();
    authorSearch->show();
    searchBtn->show();
    returnBtn->show();
}

void Menu::HidePaging()
{
    pageEnter->hide();
    pages->hide();
    goToPage->hide();
}

void Menu::ShowPaging()
{
    pageEnter->show();
    pages->show();
    goToPage->show();
}

SearchingItems* Menu::GetSearchingWidget()
{
    return searching;
}
