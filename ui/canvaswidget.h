#ifndef CANVASWIDGET_H
#define CANVASWIDGET_H

#include <QWidget>
#include <QImage>

#define MIN_WIDTH 100
#define MIN_HEIGHT 100
#define MAX_WIDTH 8000
#define MAX_HEIGHT 8000

class CanvasWidget : public QWidget
{
    Q_OBJECT

public:
    explicit CanvasWidget(QWidget *parent = nullptr);

    void readImage(QString filepath);
    void readImage(QImage image);
    void fitImage(int scale = 1);

    void zoomIn();
    void zoomOut();
    double getScale();

private:
    QImage *image;
    double scale, minScale, maxScale;
    void paintEvent(QPaintEvent* event) override;
    void wheelEvent(QWheelEvent *event) override;
    void updateScaleRange();

signals:

};

#endif // CANVASWIDGET_H
