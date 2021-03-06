#ifndef SEAMCARVINGOPERATIONWIDGET_H
#define SEAMCARVINGOPERATIONWIDGET_H

#include <QWidget>
#include <QSlider>
#include <vector>
#include "ui/canvaswidget.h"
using namespace std;

class SeamCarvingOperationWidget : public QWidget
{
    Q_OBJECT
public:
    SeamCarvingOperationWidget(QWidget *parent, CanvasWidget *canvas, bool isVertical);

private:
    QSlider *slider;
    CanvasWidget *canvas;
    bool isHorizontal;
    int lastValue, maxValue, currIndex;
    vector<QImage> undoList;
    void paintEvent(QPaintEvent *) override;

private slots:
    void setSeamCarvingValue(int value);

};

#endif // SEAMCARVINGOPERATIONWIDGET_H
