#ifndef PROFILE_H
#define PROFILE_H

#include <QWidget>
#include <QLabel>
#include <QPushButton>
#include <QVBoxLayout>
#include <QPixmap>

#define defaultImage "D:\\University\\Course Work\\BookerClass\\Data\\Program Images\\EmptyProfilePhotoTr.jpg"

class Database;
class User;

class Profile : public QWidget
{
    Q_OBJECT
public:
    explicit Profile(QWidget *parent = nullptr, Database* database = nullptr, User* user = nullptr);

    QLabel* GetImageLabel();
    QLabel* GetLoginLabel();

private:
    Database* database;
    User* user;

    QVBoxLayout* vbox;
    QLabel* image;
    QLabel* login;
    QPixmap* map;
    QSize* mapSize;
    QPushButton* changeBtn;
    QPushButton* quitBtn;

public slots:
    void on_changeBtn_clicked();
};

#endif // PROFILE_H
