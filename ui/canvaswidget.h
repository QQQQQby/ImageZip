#ifndef CANVASWIDGET_H
#define CANVASWIDGET_H

#include <QWidget>
#include <QImage>

#define MIN_WIDTH 1
#define MIN_HEIGHT 1
#define MAX_WIDTH 8000
#define MAX_HEIGHT 8000

class CanvasWidget : public QWidget
{
    Q_OBJECT

public:
    QImage *image;
    explicit CanvasWidget(QWidget *parent = nullptr);

    void readImage(QString filepath);
    void readImage(QImage image);
    void fitImage(double scale = 1);
    void clearImage();

    void saveImage(QString filepath);
    void zoomIn();
    void zoomOut();
    double getScale();

private:
    double scale, minScale, maxScale;
    void paintEvent(QPaintEvent* event) override;
    void wheelEvent(QWheelEvent *event) override;
    void updateScaleRange();

signals:

};

#endif // CANVASWIDGET_H
