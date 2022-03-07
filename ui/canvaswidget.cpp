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
    scale = minScale = maxScale = 1;
}

void CanvasWidget::readImage(QString filepath){
    delete image;
    image = new QImage();
    QImageReader reader(filepath);
    reader.read(image);

    updateScaleRange();
    fitImage();
}

void CanvasWidget::readImage(QImage another){
    delete image;
    image = new QImage(another);

    updateScaleRange();
    fitImage(scale);
}

void CanvasWidget::fitImage(int scale){
    this->scale = fmin(fmax(scale, minScale), maxScale);
    setMinimumSize(this->scale*image->width(), this->scale*image->height());
    repaint();
}

void CanvasWidget::zoomIn(){
    scale = fmin(scale * 1.2, maxScale);
    setMinimumSize(scale*image->width(), scale*image->height());
    repaint();
}

void CanvasWidget::zoomOut(){
    scale = fmax(scale * 0.8, minScale);
    setMinimumSize(scale*image->width(), scale*image->height());
    repaint();
}

double CanvasWidget::getScale() {
	return scale;
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

void CanvasWidget::updateScaleRange(){
    if(image == nullptr){
        minScale = maxScale = 1;
        return;
    }
    minScale = fmax(MIN_WIDTH/(double)image->width(), MIN_HEIGHT/(double)image->height());
    maxScale = fmin(MAX_WIDTH/(double)image->width(), MAX_HEIGHT/(double)image->height());
}
