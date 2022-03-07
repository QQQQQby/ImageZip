#include "mainwindow.h"
#include "ui_mainwindow.h"

#include<QDebug>
#include<QFileDialog>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    // Actions
    imageOpenAction = new QAction(QIcon(":/open"), "Open Image", this);
    imageOpenAction->setShortcut(QKeySequence::Open);
    imageOpenAction->setToolTip("Open a image file.");
    connect(imageOpenAction, SIGNAL(triggered()), this, SLOT(openImage()));

    seamCarvingAction = new QAction(QIcon(":/seam"), "Seam Carving", this);
    imageOpenAction->setToolTip("Run algorithm Seam Carving.");
//    connect(seamCarvingAction, SIGNAL(triggered()), this, SLOT(seamCarving()));

    // Menus
    QMenu *fileMenu = new QMenu("&File", this);
    fileMenu->addAction(imageOpenAction);

    // Menu Bar
    QMenuBar *menuBar = this->menuBar();
    menuBar->addMenu(fileMenu);

    // Tool Bar
    ui->toolBar->addAction(seamCarvingAction);
//    ui->toolBar->addSeparator();

    // Canvas
    canvas = new CanvasWidget(this);
    scrollArea = new QScrollArea;
    scrollArea->setWidget(canvas);
    scrollArea->setWidgetResizable(true);
    setCentralWidget(scrollArea);

    state = INITIAL_STATE;
    seamCarvingAction->setEnabled(false);
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::openImage(){
    if(state == INITIAL_STATE){

    }
    QString filepath = QFileDialog::getOpenFileName(this, qAppName() + " - Choose image.", ".", "image(*.jpg *.png)");
    if(filepath == "")
        return;
    canvas->readImage(filepath);

    state = IMAGE_LOADED_STATE;
//    canvas->setMinimumSize(scrollArea->width()-2, scrollArea->height()-2);

}
