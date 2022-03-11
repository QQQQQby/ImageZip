#include "seamcarvingoperationwidget.h"
#include "ui/canvaswidget.h"
#include "utils/seamcarving.h"

#include <QSlider>
#include <QVBoxLayout>
#include <QStyleOption>
#include <QPainter>
#include <QDebug>
#include <QRgb>

SeamCarvingOperationWidget::SeamCarvingOperationWidget(QWidget *parent, CanvasWidget *canvas, bool isHorizontal) : QWidget(parent)
{
    int max = isHorizontal ? canvas->image->height() : canvas->image->width();
    slider = new QSlider(this);
    slider->setOrientation(Qt::Horizontal);
    slider->setMinimum(1);
//    slider->setSingleStep(1);
    slider->setMaximum(max);
    slider->setValue(max);
    connect(slider, SIGNAL(valueChanged(int)), this, SLOT(setSeamCarvingValue(int)));

    QVBoxLayout *layout = new QVBoxLayout;
    layout->addWidget(slider);
    layout->addStretch();
    setLayout(layout);

    this->canvas = canvas;
    this->isHorizontal = isHorizontal;
    lastValue = max;
}

void SeamCarvingOperationWidget::paintEvent(QPaintEvent *){
    QStyleOption option;
    option.init(this);
    QPainter painter(this);
    style()->drawPrimitive(QStyle::PE_Widget, &option, &painter, this);
}

void SeamCarvingOperationWidget::setSeamCarvingValue(int value){
    qDebug() << lastValue << "->" << value;
    QSize originalSize = canvas->image->size();
    if(lastValue <= value)
        return;

    QImage image = canvas->image->copy();
    if(isHorizontal){
        for (int i = lastValue; i > value; --i){
            int *seam = SeamCarving::findHorizontalSeam(&image);
            image = SeamCarving::removeHorizontalSeam(&image, seam);
        }
    }else{
        for (int i = lastValue; i > value; --i){
            int *seam = SeamCarving::findVerticalSeam(&image);
            image = SeamCarving::removeVerticalSeam(&image, seam);
        }
    }
    canvas->readImage(image);

    lastValue = value;

    qDebug() << originalSize << "->" << canvas->image->size();
}
