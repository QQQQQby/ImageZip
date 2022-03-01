#include <QPainter>
#include <QPen>

#include "canvaswidget.h"

CanvasWidget::CanvasWidget(QWidget *parent) : QWidget(parent)
{

}

void CanvasWidget::paintEvent(QPaintEvent* event){
    QPainter painter(this);
    QPen pen;
    pen.setWidth(5);
    pen.setColor(Qt::blue);
    painter.setPen(pen);
    painter.drawLine(QPointF(0, height()), QPointF(width(), 0));
    painter.drawLine(QPointF(0, 0), QPointF(width(), height()));
    painter.drawRect(0, 0, width(), height());
}
