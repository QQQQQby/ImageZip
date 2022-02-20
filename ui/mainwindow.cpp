#include "mainwindow.h"
#include "ui_mainwindow.h"

#include <QDebug>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    // Actions
    QAction *imageOpenAction = new QAction(QIcon(":/open"), "Open Image", this);
    imageOpenAction->setShortcut(QKeySequence::Open);
    imageOpenAction->setToolTip("Open a image file.");
    connect(imageOpenAction, SIGNAL(triggered()), this, SLOT(openImage()));

    // Menus
    QMenu *fileMenu = new QMenu("&File", this);
    fileMenu->addAction(imageOpenAction);

    // Menu Bar
    QMenuBar *menuBar = this->menuBar();
    menuBar->addMenu(fileMenu);

    // Tool Bar
    ui->toolBar->addAction(imageOpenAction);
    ui->toolBar->addSeparator();

}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::openImage(){
    qDebug() << "123";
}
