#include "mylabel.h"
//#include "mainwindow.h"

MyLabel::MyLabel(QWidget* parent) : QLabel(parent) {}

void MyLabel::mousePressEvent(QMouseEvent* event)
{
    w->SetBookPage(this->index, this->wType);
}

void MyLabel::SetIndex(int index)
{
    this->index = index;
}

void MyLabel::SetWindow(MainWindow *w)
{
    this->w = w;
}

void MyLabel::SetWType(int type)
{
    this->wType = type;
}
