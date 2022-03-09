#include "seamcarvingoperationwidget.h"
#include "ui/canvaswidget.h"

#include <QSlider>
#include <QVBoxLayout>
#include <QStyleOption>
#include <QPainter>
#include <QDebug>
#include <QRgb>

SeamCarvingOperationWidget::SeamCarvingOperationWidget(QWidget *parent, CanvasWidget *canvas, bool isVertical) : QWidget(parent)
{
    int max = isVertical ? canvas->image->height() : canvas->image->width();

    slider = new QSlider(this);
    slider->setOrientation(Qt::Horizontal);
    slider->setMinimum(1);
    slider->setSingleStep(1);
    slider->setMaximum(max);
    slider->setValue(max);
    connect(slider, SIGNAL(valueChanged(int)), this, SLOT(setSeamCarvingValue(int)));

    QVBoxLayout *layout = new QVBoxLayout;
    layout->addWidget(slider);
    layout->addStretch();
    setLayout(layout);

    this->canvas = canvas;
    this->isVertical = isVertical;
    lastValue = max;
}

void SeamCarvingOperationWidget::paintEvent(QPaintEvent *){
    QStyleOption option;
    option.init(this);
    QPainter painter(this);
    style()->drawPrimitive(QStyle::PE_Widget, &option, &painter, this);
}

void SeamCarvingOperationWidget::setSeamCarvingValue(int value){
    QRgb color = canvas->image->pixel(69, 17);
    qDebug() << value << qRed(color) << qGreen(color) << qBlue(color);
//    qDebug() << canvas->getPixel(0, 0, 0) << canvas->getPixel(0, 0, 1) << canvas->getPixel(0, 0, 2);

}
