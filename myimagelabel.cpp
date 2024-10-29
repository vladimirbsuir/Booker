#include "myimagelabel.h"
#include "bookpage.h"

MyImageLabel::MyImageLabel(QWidget* parent, BookPage* page) : QLabel(parent)
{
    this->page = page;
    qDebug() << page;
}

void MyImageLabel::mousePressEvent(QMouseEvent* event)
{
    page->ChangeFeatureImage();
}
