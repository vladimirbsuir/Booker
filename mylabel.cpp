#include "mylabel.h"
//#include "mainwindow.h"

MyLabel::MyLabel(QWidget* parent) : QLabel(parent) {}

void MyLabel::mousePressEvent(QMouseEvent* event)
{
    w->SetBookPage(this->index);
}

void MyLabel::SetIndex(int index)
{
    this->index = index;
}

void MyLabel::SetWindow(MainWindow *w)
{
    this->w = w;
}
