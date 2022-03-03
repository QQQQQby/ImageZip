#include <cmath>
#include <QDebug>
#include <QPainter>
#include <QPen>
#include <QImageReader>
#include <QPixmap>
#include <QApplication>
#include <QWheelEvent>

#include "canvaswidget.h"

CanvasWidget::CanvasWidget(QWidget *parent) : QWidget(parent)
{
    image = nullptr;
    scale = 0;
}

void CanvasWidget::readImage(QString filepath){
    delete image;
    image = new QImage();
    QImageReader reader(filepath);
    reader.read(image);
    setMinimumSize(image->width(), image->height());
    scale = 1;
    repaint();
}

void CanvasWidget::zoomIn(){
    scale = fmin(scale * 1.2, 5);
    setMinimumSize(scale*image->width(), scale*image->height());
    repaint();
}

void CanvasWidget::zoomOut(){
    scale = fmax(scale * 0.8, 1e-2);
    setMinimumSize(scale*image->width(), scale*image->height());
    repaint();
}

void CanvasWidget::paintEvent(QPaintEvent* event){
    QPainter painter(this);
    QPen pen;
    painter.setPen(pen);
    if(image != nullptr){
        if(abs(scale - 1) <= 1e-6)
            painter.drawImage(0, 0, *image);
        else
            painter.drawPixmap(0, 0, QPixmap::fromImage(image->scaled(scale*image->width(), scale*image->height())));
    }
}

void CanvasWidget::wheelEvent(QWheelEvent *event){
    if(image != nullptr && QApplication::keyboardModifiers() == Qt::ControlModifier){
        if(event->delta() > 0)
            zoomIn();
        else
            zoomOut();
        event->accept();
    }
}
