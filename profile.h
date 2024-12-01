#ifndef PROFILE_H
#define PROFILE_H

#include <QWidget>
#include <QLabel>
#include <QPushButton>
#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QPixmap>

#define defaultImage "D:\\University\\Course Work\\BookerClass\\Data\\Program Images\\EmptyProfilePhotoTr.jpg"
#define aLogin "Vladimir"
#define aPass "Ganetsky"

class Database;
class User;
class Widget;

class Profile : public QWidget
{
    Q_OBJECT
public:
    explicit Profile(QWidget *parent = nullptr, Database* database = nullptr, User* user = nullptr, Widget* catalog = nullptr);

    QLabel* GetImageLabel();
    QLabel* GetLoginLabel();
    QPushButton* GetAddItemBtn();
    QPushButton* GetUpdateItemBtn();
    QPushButton* GetDeleteItemBtn();
    void ShowABtns();

private:
    Database* database;
    User* user;
    Widget* catalog;

    QHBoxLayout* hbox;
    QHBoxLayout* hbox2;
    QVBoxLayout* vbox;
    QVBoxLayout* vbox2;
    QVBoxLayout* vboxMain;
    QLabel* image;
    QLabel* login;
    QPixmap* map;
    QSize* mapSize;
    QPushButton* addItemBtn;
    QPushButton* updateItemBtn;
    QPushButton* deleteItemBtn;
    QPushButton* changeBtn;
    QPushButton* quitBtn;

public slots:
    void on_changeBtn_clicked();
    void on_addItemBtn_clicked();
    void on_updateItemBtn_clicked();
    void on_deleteItemBtn_clicked();
};

#endif // PROFILE_H
