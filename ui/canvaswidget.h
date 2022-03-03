#ifndef CANVASWIDGET_H
#define CANVASWIDGET_H

#include <QWidget>
#include <QImage>

class CanvasWidget : public QWidget
{
    Q_OBJECT

public:
    explicit CanvasWidget(QWidget *parent = nullptr);

    void readImage(QString filepath);
    void zoomIn();
    void zoomOut();

private:
    QImage *image;
    double scale;
    void paintEvent(QPaintEvent* event) override;
    void wheelEvent(QWheelEvent *event) override;

signals:

};

#endif // CANVASWIDGET_H
