#ifndef REGAUTHPAGE_H
#define REGAUTHPAGE_H

#include <QWidget>
#include <QLabel>
#include <QPushButton>
#include <QLineEdit>
#include <QVBoxLayout>
#include <QMessageBox>

#include <database.h>

class Widget;
class Menu;
class User;
class Profile;

class RegAuthPage : public QWidget
{
    Q_OBJECT
public:
    explicit RegAuthPage(QWidget *parent = nullptr, Widget* catalog = nullptr, Menu* menu = nullptr, Database* database = nullptr, User* user = nullptr, Profile* profile = nullptr);

    void SetProfile();
    void SendMail(QString, int);

private:
    QVBoxLayout* vbox;
    QLabel* title;
    QPushButton* regBtn;
    QPushButton* authBtn;
    QLabel* loginLabel;
    QLabel* passLabel;
    QLabel* confPassLabel;
    QLabel* emailLabel;
    QLabel* confEmailLabel;
    QLineEdit* login;
    QLineEdit* pass;
    QLineEdit* confPass;
    QLineEdit* email;
    QLineEdit* confEmail;
    QPushButton* enterBtn;
    QPushButton* backBtn;


    Widget* catalog;
    Menu* menu;
    Database* database;
    User* user;
    Profile* profile;

public slots:
    void on_regBtn_clicked();
    void on_authBtn_clicked();
    void on_enterBtn_clicked();
    void on_backBtn_clicked();

};

#endif // REGAUTHPAGE_H
