#include "regauthpage.h"
#include "mainwindow.h"
#include "widget.h"
#include "user.h"
#include "profile.h"
#include "smtp.h"

#include <QPainter>
#include <QPixmap>
#include <QBrush>
#include <QImage>

#include <QRegularExpression>
#include <QRandomGenerator>

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
    emailLabel = new QLabel("Email");
    confEmailLabel = new QLabel("Code was send to the email. Enter it in the field below:");
    confPassLabel = new QLabel("Confirm password");
    login = new QLineEdit();
    pass = new QLineEdit();
    confPass = new QLineEdit();
    email = new QLineEdit();
    confEmail = new QLineEdit();

    login->setMaxLength(25);
    confEmail->setMaxLength(6);

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
    emailLabel->setStyleSheet("font-size: 30px");
    confPassLabel->setStyleSheet("font-size: 30px");
    loginLabel->setAlignment(Qt::AlignCenter);
    passLabel->setAlignment(Qt::AlignCenter);
    confPassLabel->setAlignment(Qt::AlignCenter);

    login->setFixedWidth(200);
    pass->setFixedWidth(200);
    confPass->setFixedWidth(200);
    email->setFixedWidth(200);;
    confEmail->setFixedWidth(200);

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
    vbox->addWidget(emailLabel);
    vbox->addWidget(email);
    vbox->addSpacing(25);
    vbox->addWidget(confEmailLabel);
    vbox->addWidget(confEmail);
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
    vbox->setAlignment(email, Qt::AlignHCenter);
    vbox->setAlignment(emailLabel, Qt::AlignHCenter);
    vbox->setAlignment(confEmail, Qt::AlignHCenter);
    vbox->addWidget(confEmailLabel);

    loginLabel->hide();
    login->hide();
    passLabel->hide();
    pass->hide();
    emailLabel->hide();
    email->hide();
    confPassLabel->hide();
    confPass->hide();
    confEmailLabel->hide();
    confEmail->hide();
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
    emailLabel->hide();
    email->hide();
    confEmailLabel->hide();
    confEmail->hide();
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
    emailLabel->show();
    email->show();
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
        if (email->text() == "")
        {
            QMessageBox::about(this, "Warning", "Enter email");
            return;
        }

        int value = 0;
        if (confEmail->isHidden())
        {
            // Send email
            std::uniform_int_distribution dist(100000, 10000000);
            value = dist(*QRandomGenerator::global());

            SendMail(email->text(), value);

            confEmailLabel->show();
            confEmail->show();
            return;
        }
        else
        {
            if (!(confEmail->text().toInt() == value))
            {
                QMessageBox::about(this, "Warning", "Code is incorrect");
                return;
            }
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

void RegAuthPage::SendMail(QString recipient, int value)
{
    Smtp* smtp = new Smtp("billysammers2000@gmail.com", "Vova19436", "smtp.gmail.com", 465);
    //connect(smtp, SIGNAL(status(QString)), this, SLOT(mailSent(QString)));

    smtp->sendMail("billysammers2000@gmail.com", recipient, "Code", QString::number(value));
}
