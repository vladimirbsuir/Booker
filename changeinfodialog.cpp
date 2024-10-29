#include "changeinfodialog.h"
#include "database.h"

ChangeInfoDialog::ChangeInfoDialog(QWidget *parent, Database* database)
    : QDialog{parent}
{
    this->database = database;

    vbox = new QVBoxLayout();
    changeLogin = new QPushButton("Change login");
    changePass = new QPushButton("Change password");
    changeImage = new QPushButton("Change image");
    agreeInfo = new QPushButton("Enter");
    backBtn = new QPushButton("Back");
    enterInfo = new QLineEdit();
    confirmInfo = new QLineEdit();
    enterText = new QLabel();
    confirmText = new QLabel("Confirm new password:");
    confirmText->hide();
    backBtn->hide();

    connect(changeLogin, SIGNAL(clicked()), SLOT(on_changeLoginBtn_clicked()));
    connect(changePass, SIGNAL(clicked()), SLOT(on_changePassBtn_clicked()));
    connect(changeImage, SIGNAL(clicked()), SLOT(on_changeImageBtn_clicked()));

    vbox->addWidget(changeLogin);
    vbox->addWidget(changePass);
    vbox->addWidget(changeImage);
    vbox->addWidget(enterText);
    vbox->addWidget(enterInfo);
    vbox->addWidget(confirmText);
    vbox->addWidget(confirmInfo);
    vbox->addWidget(agreeInfo);
    vbox->addStretch(0);
    vbox->addWidget(backBtn);

    enterInfo->hide();
    confirmInfo->hide();
    agreeInfo->hide();

    this->setLayout(vbox);

    connect(agreeInfo, SIGNAL(clicked()), SLOT(on_agreeInfoBtn_clicked()));
    connect(backBtn, SIGNAL(clicked()), SLOT(on_backBtn_clicked()));
}

void ChangeInfoDialog::on_agreeInfoBtn_clicked()
{
    if (confirmInfo->isHidden())
    {
        if (enterInfo->text().size() > 20)
        {
            QMessageBox::about(this, "Warning", "Login shouldn't be longer than 20 symbols");

            return;
        }

        if(!database->UpdateUser(enterInfo->text(), 0)) QMessageBox::about(this, "Warning", "There is no such user");
    }
    else
    {
        if (!database->UpdateUser(enterInfo->text(), 1)) QMessageBox::about(this, "Warning", "There is no such user");

        confirmInfo->hide();
        confirmInfo->clear();
        confirmText->hide();
    }

    changeLogin->show();
    changePass->show();
    changeImage->show();
    enterInfo->hide();
    agreeInfo->hide();
    enterText->hide();
    backBtn->hide();
    enterInfo->clear();
}

void ChangeInfoDialog::on_backBtn_clicked()
{
    if (!confirmInfo->isHidden())
    {
        confirmInfo->hide();
        confirmInfo->clear();
        confirmText->hide();
    }

    changeLogin->show();
    changePass->show();
    changeImage->show();
    enterInfo->hide();
    agreeInfo->hide();
    enterText->hide();
    enterInfo->clear();
    backBtn->hide();
}

void ChangeInfoDialog::on_changeLoginBtn_clicked()
{
    changeLogin->hide();
    changePass->hide();
    changeImage->hide();
    enterInfo->show();
    agreeInfo->show();
    enterText->setText("Enter new login:");
    enterText->show();
    backBtn->show();
}

void ChangeInfoDialog::on_changePassBtn_clicked()
{
    changePass->hide();
    changeLogin->hide();
    changeImage->hide();
    enterInfo->show();
    confirmInfo->show();
    agreeInfo->show();
    enterText->setText("Enter new password:");
    enterText->show();
    confirmText->show();
    backBtn->show();
}

void ChangeInfoDialog::on_changeImageBtn_clicked()
{
    QString imagePath;
    imagePath = QFileDialog::getOpenFileName(this, "Choose image", "C://", "jpeg (*.jpg);; png (*.png);");
    //qDebug() << imagePath;

    if (!database->UpdateUser(imagePath, 2)) QMessageBox::about(this, "Warning", "There is no such user");
}
