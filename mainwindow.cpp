#include "mainwindow.h"
#include "widget.h"
#include "user.h"
#include "profile.h"
#include "myimagelabel.h"
#include "featured.h"
#include "combase.h"
#include <QCloseEvent>
#include "item.h"
#include "searchingitems.h"

MainWindow::MainWindow(QWidget *parent)
    : QWidget{parent}
{
    user = new User();
    database = new Database(user);
    combase = new Combase();
    //combase = nullptr;

    catalog = new Widget(nullptr, this);
    hbox = new QHBoxLayout();

    //catalog->SetMainW(this);

    // Profile
    profile = new Profile(nullptr, database, user, catalog);

    // Featured
    featured = new Featured(nullptr, user, catalog, this);

    // Book page
    page = new BookPage(nullptr, catalog, user, featured, combase);

    // Searching
    searching = new SearchingItems(nullptr, this);

    // Menu
    menu = new Menu(nullptr, catalog, profile, page, database, user, featured, searching);
    menu->hide();
    page->SetMenu(menu);
    // -------------------------------

    // Registration and authorization
    regAuth = new RegAuthPage(nullptr, catalog, menu, database, user, profile);

    /*QWidget* w3 = new QWidget();
    QLabel* labb = new QLabel("Labbb");
    QVBoxLayout* vbox2 = new QVBoxLayout();
    vbox2->addWidget(labb);
    w3->setLayout(vbox2);*/

    hbox->addWidget(regAuth);
    hbox->addWidget(menu);
    hbox->addWidget(catalog->GetArea());
    hbox->addWidget(searching->GetArea());
    hbox->addWidget(page);
    hbox->addWidget(profile);
    hbox->addWidget(featured->GetArea());
    page->hide();
    profile->hide();
    hbox->setContentsMargins(0,0,0,0);
    hbox->setSpacing(0);
    //hbox->addWidget(w3);

    //catalog->GetTitles();

    this->setLayout(hbox);

    //catalog->GetArea()->hide();

    //w3->show();
    //catalog->GetArea()->show();
    catalog->GetArea()->hide();
    this->show();
}

void MainWindow::SetBookPage(int index, int type)
{
    int isFeatured = 0;
    /*<QString>* titles = catalog->GetTitlesV();
    QVector<QString>* images = catalog->GetImagesV();
    QVector<QString>* desc = catalog->GetDescV();
    QVector<QString>* authors = catalog->GetAuthorsV();*/

    //QVector<Item*>* books = catalog->GetBooks();
    QVector<Item*>* books;
    int isSBooks = 0;
    if (index >= 90)
    {
        books = catalog->GetSBooks();
        index -= 90;
        isSBooks = 1;
    }
    else books = catalog->GetBooks();

    QVector<QString>* data = combase->GetComments((*books)[index]->GetValues()[2]);

    try
    {
        page->FillComments(data);
    }
    catch(std::overflow_error& e)
    {
        qDebug() << e.what();
    }

    page->CommentExist(data);

    page->GetTitle()->setText((*books)[index]->GetValues()[2] + " | " + (*books)[index]->GetValues()[3]);
    page->GetDesc()->setText((*books)[index]->GetValues()[1]);
    page->GetImage()->setAlignment(Qt::AlignCenter);
    page->GetTitle()->setAlignment(Qt::AlignCenter);

    page->SetStrTitle((*books)[index]->GetValues()[2]);

    if (isSBooks == 1) page->SetIndex(index + 90);
    else page->SetIndex(index);

    page->SetWType(type);
//
    QPixmap im((*books)[index]->GetValues()[0]);
    QSize PicSize(300, 500);
    im = im.scaled(PicSize, Qt::KeepAspectRatio);
    page->GetImage()->setPixmap(im);
//
    if (isSBooks == 1) index += 90;

    QStringList* featuredBooks = user->GetFeatured();
    if (!featuredBooks->isEmpty())
    {
        if (featuredBooks->contains(QString::number(index))) isFeatured = 1;
        else isFeatured = 0;
    }
    else isFeatured = 0;

    QPixmap featImage;
    if (isFeatured) featImage.load("D:\\University\\Course Work\\BookerClass\\Data\\Program Images\\AddedToFeatured.jpg");
    else featImage.load("D:\\University\\Course Work\\BookerClass\\Data\\Program Images\\AddToFeatured.jpg");
    page->SetState(isFeatured);

    QSize featSize(50, 50);
    featImage = featImage.scaled(featSize, Qt::KeepAspectRatio);
    page->GetFeatureImage()->setPixmap(featImage);

    if (type == 1)
    {
        catalog->GetArea()->hide();
        menu->HidePaging();
        menu->HideSearching();
    }
    else if (type == 2)
    {
        featured->GetArea()->hide();
    }
    else if (type == 3)
    {
        searching->GetArea()->hide();
        menu->HidePaging();
        menu->HideSearching();
    }

    page->show();
}

void MainWindow::closeEvent(QCloseEvent *event)
{
    if (user->GetFeatured() != nullptr) database->UpdateUser(user->GetFeatured()->join(" "), 3);
    event->accept();
}
