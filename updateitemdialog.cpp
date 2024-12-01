#include "updateitemdialog.h"
#include "widget.h"
#include "bookbase.h"
#include "sbookbase.h"

#include <QMessageBox>
#include <QButtonGroup>

UpdateItemDialog::UpdateItemDialog(QWidget* parent, Widget* catalog) : QDialog(parent) {
    this->catalog = catalog;

    titleEdit = new QLineEdit();
    descEdit = new QTextEdit();
    titleLabel = new QLabel("Enter title of the book:");
    descLabel = new QLabel("Enter new description:");
    itemType = new QLabel("Choose item type:");
    bookType = new QRadioButton("Book");
    sbookType = new QRadioButton("Serial book");
    enterBtn = new QPushButton("Enter");
    searchTypeLabel = new QLabel("Search by:");
    idSearch = new QRadioButton("ID");
    titleSearch = new QRadioButton("Title");
    vbox = new QVBoxLayout();

    bookType->setChecked(true);
    titleSearch->setChecked(true);

    typeGroup = new QButtonGroup();
    typeGroup->addButton(bookType);
    typeGroup->addButton(sbookType);
    searchGroup = new QButtonGroup();
    searchGroup->addButton(idSearch);
    searchGroup->addButton(titleSearch);

    vbox->addWidget(itemType);
    vbox->addWidget(bookType);
    vbox->addWidget(sbookType);
    vbox->addWidget(searchTypeLabel);
    vbox->addWidget(idSearch);
    vbox->addWidget(titleSearch);
    vbox->addWidget(titleLabel);
    vbox->addWidget(titleEdit);
    vbox->addWidget(descLabel);
    vbox->addWidget(descEdit);
    vbox->addWidget(enterBtn);

    this->setLayout(vbox);

    connect(enterBtn, SIGNAL(clicked()), SLOT(on_enterBtn_clicked()));
    connect(sbookType, SIGNAL(clicked()), SLOT(on_sbookBtn_toggled()));
    connect(bookType, SIGNAL(clicked()), SLOT(on_bookBtn_toggled()));
    connect(idSearch, SIGNAL(clicked()), SLOT(on_idSearchBtn_toggled()));
    connect(titleSearch, SIGNAL(clicked()), SLOT(on_titleSearchBtn_toggled()));
}

void UpdateItemDialog::on_enterBtn_clicked()
{
    QString title = titleEdit->text();
    QString desc = descEdit->toPlainText();

    if (title == "")
    {
        QMessageBox::warning(this, "Warning", "Title field is empty");
        return;
    }
    else if (desc == "")
    {
        QMessageBox::warning(this, "Warning", "Description field is empty");
        return;
    }

    bool isNum;
    int verifyNum = title.toInt(&isNum);
    if (isNum && titleSearch->isChecked())
    {
        QMessageBox::warning(this, "Warning", "Search by title using id, needed title");
        return;
    }
    else if (!isNum && idSearch->isChecked())
    {
        QMessageBox::warning(this, "Warning", "Search by id using title, needed id");
        return;
    }

    int type = 0;
    if (idSearch->isChecked()) type = 2;
    else if (titleSearch->isChecked()) type = 1;

    if (bookType->isChecked())
    {
        if (catalog->GetBookbase()->Update(title, type, desc))
        {
            titleEdit->clear();
            descEdit->clear();
            QMessageBox::about(this, "Info", "Information was successfully updated");
        }
        else QMessageBox::about(this, "Info", "Information wasn't updated");
    }
    else if (sbookType->isChecked())
    {
        if (catalog->GetSBookbase()->Update(title, type, desc))
        {
            titleEdit->clear();
            descEdit->clear();
            QMessageBox::about(this, "Info", "Information was successfully updated");
        }
        else QMessageBox::about(this, "Info", "Information wasn't updated");
    }
}

void UpdateItemDialog::on_sbookBtn_toggled()
{
    if (!idSearch->isHidden())
    {
        idSearch->hide();
        titleSearch->setChecked(true);
    }
}

void UpdateItemDialog::on_bookBtn_toggled()
{
    if (idSearch->isHidden())
    {
        idSearch->show();
    }
}

void UpdateItemDialog::on_idSearchBtn_toggled()
{
    titleLabel->setText("Enter id of the book:");
}

void UpdateItemDialog::on_titleSearchBtn_toggled()
{
    titleLabel->setText("Enter title of the book:");
}
