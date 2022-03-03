#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QScrollArea>

#include "canvaswidget.h"

#define INITIAL_STATE 0
#define IMAGE_LOADED_STATE 1
#define OPERATE_STATE 2

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private:
    Ui::MainWindow *ui;
    QAction *imageOpenAction;
    QScrollArea *scrollArea;
    CanvasWidget *canvas;
    int state;

private slots:
    void openImage();
};
#endif // MAINWINDOW_H
