#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QScrollArea>

#include "canvaswidget.h"

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
    QAction *seamCarvingAction;
    QScrollArea *scrollArea;
    CanvasWidget *canvas;
    bool isLoaded;
//    void switchState(int state);


private slots:
    void openImage();
    void showHSeamCarvingOperation(bool checked);
};
#endif // MAINWINDOW_H
