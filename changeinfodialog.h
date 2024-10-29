#ifndef CHANGEINFODIALOG_H
#define CHANGEINFODIALOG_H

#include <QDialog>
#include <QPushButton>
#include <QVBoxLayout>
#include <QLineEdit>
#include <QMessageBox>
#include <QLabel>
#include <QFileDialog>

class Database;

class ChangeInfoDialog : public QDialog
{
    Q_OBJECT
public:
    explicit ChangeInfoDialog(QWidget *parent = nullptr, Database* database = nullptr);

private:
    Database* database;

    QVBoxLayout* vbox;
    QPushButton* changeLogin;
    QPushButton* changePass;
    QPushButton* changeImage;
    QPushButton* backBtn;
    QLineEdit* enterInfo;
    QLineEdit* confirmInfo;
    QPushButton* agreeInfo;
    QLabel* enterText;
    QLabel* confirmText;

public slots:
    void on_changeLoginBtn_clicked();
    void on_changePassBtn_clicked();
    void on_changeImageBtn_clicked();
    void on_agreeInfoBtn_clicked();
    void on_backBtn_clicked();
};

#endif // CHANGEINFODIALOG_H
