#include "menu.h"
#include "widget.h"
#include "profile.h"
#include "bookpage.h"
#include "database.h"
#include "user.h"
#include "featured.h"

#include <QMessageBox>

#define btnH 100

Menu::Menu(QWidget *parent, Widget* catalog, Profile* profile, BookPage* page, Database* database, User* user, Featured* featured)
    : QWidget{parent}
{
    this->featured = featured;
    this->catalog = catalog;
    this->profile = profile;
    this->page = page;
    this->database = database;
    this->user = user;

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

    vboxCatalog->addWidget(pages);
    vboxCatalog->addWidget(pageEnter);
    vboxCatalog->addWidget(goToPage);

    catalogAdd->setLayout(vboxCatalog);
    vbox->addWidget(catalogAdd);

    vbox->addStretch(0);

    vbox->addWidget(quitBtn);

    //vbox->addStretch(0);
    vbox->setContentsMargins(0,0,0,0);

    this->setLayout(vbox);

    connect(profileBtn, SIGNAL(clicked()), SLOT(on_profileBtn_clicked()));
    connect(catalogBtn, SIGNAL(clicked()), SLOT(on_catalogBtn_clicked()));
    connect(quitBtn, SIGNAL(clicked()), SLOT(on_quitBtn_clicked()));
    connect(featuredBtn, SIGNAL(clicked()), SLOT(on_featuredBtn_clicked()));
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
            pageEnter->hide();
            pages->hide();
            goToPage->hide();
            catalog->GetArea()->hide();
        }
        if (!page->isHidden()) page->hide();
        if (!featured->GetArea()->isHidden()) featured->GetArea()->hide();

        profile->show();
    }
}

void Menu::on_catalogBtn_clicked()
{
    if (catalog->GetArea()->isHidden())
    {
        if (!profile->isHidden()) profile->hide();
        if (!page->isHidden()) page->hide();
        if (!featured->GetArea()->isHidden()) featured->GetArea()->hide();

        pageEnter->show();
        pages->show();
        goToPage->show();

        catalog->GetArea()->show();
    }
}

void Menu::on_featuredBtn_clicked()
{
    if (featured->GetArea()->isHidden())
    {
        if (!profile->isHidden()) profile->hide();
        if (!page->isHidden()) page->hide();
        if (!catalog->GetArea()->isHidden())
        {
            pageEnter->hide();
            pages->hide();
            goToPage->hide();
            catalog->GetArea()->hide();
        }

        featured->SetBooks();
        featured->GetArea()->show();
    }
}

QLineEdit* Menu::GetLineEdit()
{
    return pageEnter;
}

QLabel* Menu::GetPages()
{
    return pages;
}

QPushButton* Menu::GetPageBtn()
{
    return goToPage;
}
