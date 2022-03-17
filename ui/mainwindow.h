#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QScrollArea>

#include "canvaswidget.h"

#define INITIAL_STATE 0
#define IMAGE_LOADED_STATE 1
#define OPERATING_STATE 2

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
    QAction *imageOpenAction, *imageSaveAction, *imageCloseAction;
    QAction *horizontalSeamCarvingAction, *verticalSeamCarvingAction;
    QScrollArea *scrollArea;
    CanvasWidget *canvas;
    int state;
    QString filepath;


private slots:
    void openImage();
    void saveImage();
    void closeImage();
    void showHorizontalSeamCarvingOperation(bool checked);
    void showVerticalSeamCarvingOperation(bool checked);

};
#endif // MAINWINDOW_H
