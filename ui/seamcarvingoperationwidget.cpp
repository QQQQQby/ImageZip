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
    maxValue = isHorizontal ? canvas->image->height() : canvas->image->width();
    slider = new QSlider(this);
    slider->setOrientation(Qt::Horizontal);
    slider->setMinimum(1);
    slider->setMaximum(maxValue);
    slider->setValue(maxValue);
    connect(slider, SIGNAL(valueChanged(int)), this, SLOT(setSeamCarvingValue(int)));

    QVBoxLayout *layout = new QVBoxLayout;
    layout->addWidget(slider);
    layout->addStretch();
    setLayout(layout);

    this->canvas = canvas;
    this->isHorizontal = isHorizontal;
    lastValue = maxValue;
    undoList.push_back(canvas->image->copy());
    currIndex = 0;
}

void SeamCarvingOperationWidget::paintEvent(QPaintEvent *){
    QStyleOption option;
    option.init(this);
    QPainter painter(this);
    style()->drawPrimitive(QStyle::PE_Widget, &option, &painter, this);
}

void SeamCarvingOperationWidget::setSeamCarvingValue(int value){
    if(lastValue == value)
        return;

    qDebug() << lastValue << "->" << value;
    int nextIndex = maxValue - value;

    if(nextIndex < (int)undoList.size()){
        // Undo
        canvas->readImage(undoList[nextIndex]);
        return;
    }

    QImage image = undoList[undoList.size() - 1];
    for (int i = (int)undoList.size() - 1; i < nextIndex; ++i){
        if(isHorizontal){
            image = SeamCarving::removeHorizontalSeam(&image, SeamCarving::findHorizontalSeam(&image));
        }else{
            image = SeamCarving::removeVerticalSeam(&image, SeamCarving::findVerticalSeam(&image));
        }
        undoList.push_back(image);
    }
    canvas->readImage(image);
    lastValue = value;
    currIndex = nextIndex;
}
