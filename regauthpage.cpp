#include "regauthpage.h"
#include "mainwindow.h"
#include "widget.h"
#include "user.h"
#include "profile.h"

#include <QPainter>
#include <QPixmap>
#include <QBrush>
#include <QImage>

#include <QRegularExpression>

RegAuthPage::RegAuthPage(QWidget *parent, Widget* catalog, Menu* menu, Database* database, User* user, Profile* profile)
    : QWidget{parent}
{
    this->catalog = catalog;
    this->menu = menu;
    this->database = database;
    this->user = user;
    this->profile = profile;

    vbox = new QVBoxLayout();
    title = new QLabel("Booker");
    regBtn = new QPushButton("Registration");
    authBtn = new QPushButton("Authorisation");
    enterBtn = new QPushButton("Enter");
    backBtn = new QPushButton("Back");
    loginLabel = new QLabel("Login");
    passLabel = new QLabel("Password");
    confPassLabel = new QLabel("Confirm password");
    login = new QLineEdit();
    pass = new QLineEdit();
    confPass = new QLineEdit();

    login->setMaxLength(25);

    title->setStyleSheet("font-size: 50px");
    title->setAlignment(Qt::AlignCenter);

    regBtn->setFixedWidth(200);
    regBtn->setMinimumHeight(100);
    authBtn->setFixedWidth(200);
    authBtn->setMinimumHeight(100);
    enterBtn->setFixedWidth(100);
    enterBtn->setMinimumHeight(50);
    //enterBtn->setStyleSheet("border: 2px solid; background-color: green");

    loginLabel->setStyleSheet("font-size: 30px");
    passLabel->setStyleSheet("font-size: 30px");
    confPassLabel->setStyleSheet("font-size: 30px");
    loginLabel->setAlignment(Qt::AlignCenter);
    passLabel->setAlignment(Qt::AlignCenter);
    confPassLabel->setAlignment(Qt::AlignCenter);

    login->setFixedWidth(200);
    pass->setFixedWidth(200);
    confPass->setFixedWidth(200);

    vbox->addWidget(title);
    vbox->addStretch(0);
    vbox->addWidget(regBtn);
    vbox->addWidget(authBtn);
    vbox->addWidget(loginLabel);
    vbox->addWidget(login);
    vbox->addSpacing(25);
    vbox->addWidget(passLabel);
    vbox->addWidget(pass);
    vbox->addSpacing(25);
    vbox->addWidget(confPassLabel);
    vbox->addWidget(confPass);
    vbox->addSpacing(25);
    vbox->addWidget(enterBtn);

    vbox->addStretch(0);
    vbox->addWidget(backBtn);

    vbox->setAlignment(regBtn, Qt::AlignHCenter);
    vbox->setAlignment(authBtn, Qt::AlignHCenter);
    vbox->setAlignment(enterBtn, Qt::AlignHCenter);
    vbox->setAlignment(login, Qt::AlignHCenter);
    vbox->setAlignment(pass, Qt::AlignHCenter);
    vbox->setAlignment(confPass, Qt::AlignHCenter);

    loginLabel->hide();
    login->hide();
    passLabel->hide();
    pass->hide();
    confPassLabel->hide();
    confPass->hide();
    enterBtn->hide();
    backBtn->hide();

    connect(regBtn, SIGNAL(clicked()), SLOT(on_regBtn_clicked()));
    connect(authBtn, SIGNAL(clicked()), SLOT(on_authBtn_clicked()));
    connect(enterBtn, SIGNAL(clicked()), SLOT(on_enterBtn_clicked()));
    connect(backBtn, SIGNAL(clicked()), SLOT(on_backBtn_clicked()));

    this->setLayout(vbox);
}

void RegAuthPage::on_backBtn_clicked()
{
    regBtn->show();
    authBtn->show();

    loginLabel->hide();
    login->hide();
    passLabel->hide();
    pass->hide();
    confPassLabel->hide();
    confPass->hide();
    enterBtn->hide();
    backBtn->hide();

    login->clear();
    pass->clear();
    confPass->clear();
}

void RegAuthPage::on_regBtn_clicked()
{
    regBtn->hide();
    authBtn->hide();

    loginLabel->show();
    login->show();
    passLabel->show();
    pass->show();
    confPassLabel->show();
    confPass->show();
    enterBtn->show();
    backBtn->show();
}

void RegAuthPage::on_authBtn_clicked()
{
    regBtn->hide();
    authBtn->hide();

    loginLabel->show();
    login->show();
    passLabel->show();
    pass->show();
    enterBtn->show();
    backBtn->show();
}

void RegAuthPage::on_enterBtn_clicked()
{
    if (login->text() == "")
    {
        QMessageBox::about(this, "Warning", "Login is empty");
        return;
    }

    if (pass->text() == "")
    {
        QMessageBox::about(this, "Warning", "Password is empty");
        return;
    }

    if (confPass->isHidden())
    {
        if (!database->CheckUser(login->text(), pass->text()))
        {
            QMessageBox::about(this, "Warning", "Incorrect login or password");
            return;
        }
    }
    else
    {
        if (confPass->text() == "")
        {
            QMessageBox::about(this, "Warning", "Confirm password");
            return;
        }
        if (pass->text() != confPass->text())
        {
            QMessageBox::about(this, "Warning", "Passwords are different");
            return;
        }

        database->InsertUser(login->text(), pass->text());
    }

    user->SetLogin(login->text());
    user->SetPass(pass->text());
    user->SetImage(database->GetUserImage());

    //
    QString featured = database->GetUserFeatured();
    QStringList* booksIndexes = new QStringList();
    if (featured != "")
    {
        (*booksIndexes) = featured.split(QRegularExpression("\\s+"), Qt::SkipEmptyParts);
    }

    user->SetFeatured(booksIndexes);
    //

    /*QImage* im = new QImage(defaultImage);
    im = &(im->convertToFormat(QImage::Format_ARGB32));
    QImage circleProfile(im->width(), im->height(), QImage::Format_ARGB32);
    circleProfile.fill(Qt::transparent);
    QBrush brush(im);
    QPainter painterr(&circleProfile);
    painterr.setBrush(brush);
    painterr.setPen(Qt::NoPen);
    painterr.setRenderHint(QPainter::Antialiasing);
    painterr.drawEllipse(0,0,im->width(), im->height());
    QPixmap mapp = QPixmap::fromImage(&im);
    profile->GetImageLabel()->setPixmap(mapp);*/

    QPixmap* map;
    if (this->user->GetImage() == "")
    {
        map = new QPixmap(defaultImage);
    }
    else map = new QPixmap(this->user->GetImage());

    QSize mapSize(300, 300);
    *map = map->scaled(mapSize, Qt::KeepAspectRatio);
    profile->GetImageLabel()->setPixmap(*map);

    this->hide();
    menu->show();
    catalog->GetArea()->show();

    SetProfile();
}

void RegAuthPage::SetProfile()
{
    profile->GetLoginLabel()->setText(login->text());
}
