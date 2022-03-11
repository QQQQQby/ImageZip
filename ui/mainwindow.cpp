#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "ui/seamcarvingoperationwidget.h"

#include <QDebug>
#include <QFileDialog>

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

    horizontalSeamCarvingAction = new QAction(QIcon(":/horizontal-seam"), "Horizontal Seam Carving", this);
    horizontalSeamCarvingAction->setToolTip("Run horizontal Seam Carving.");
    horizontalSeamCarvingAction->setCheckable(true);
    connect(horizontalSeamCarvingAction, SIGNAL(triggered(bool)), this, SLOT(showHorizontalSeamCarvingOperation(bool)));

    verticalSeamCarvingAction = new QAction(QIcon(":/vertical-seam"), "Vertical Seam Carving", this);
    verticalSeamCarvingAction->setToolTip("Run vertical Seam Carving.");
    verticalSeamCarvingAction->setCheckable(true);
    connect(verticalSeamCarvingAction, SIGNAL(triggered(bool)), this, SLOT(showVerticalSeamCarvingOperation(bool)));

    // Menus
    QMenu *fileMenu = new QMenu("&File", this);
    fileMenu->addAction(imageOpenAction);

    // Menu Bar
    QMenuBar *menuBar = this->menuBar();
    menuBar->addMenu(fileMenu);

    // Tool Bar
    ui->toolBar->addAction(horizontalSeamCarvingAction);
    ui->toolBar->addAction(verticalSeamCarvingAction);

    // Canvas
    canvas = new CanvasWidget(this);
    scrollArea = new QScrollArea;
    scrollArea->setWidget(canvas);
    scrollArea->setWidgetResizable(true);
    setCentralWidget(scrollArea);

    isLoaded = false;
    horizontalSeamCarvingAction->setEnabled(false);
    verticalSeamCarvingAction->setEnabled(false);
}

MainWindow::~MainWindow()
{
    delete ui;
}

//void MainWindow::switchState(int state){
//    switch (state) {
//    case INITIAL_STATE:
//        imageOpenAction->setEnabled(true);
//        seamCarvingAction->setEnabled(false);
//        this->state = INITIAL_STATE;
//        break;
//    case IMAGE_LOADED_STATE:
//        seamCarvingAction->setEnabled(true);

//        this->state = IMAGE_LOADED_STATE;
//        break;
//    case OPERATE_STATE:
//        seamCarvingAction->setEnabled(true);
//        this->state = OPERATE_STATE;
//        break;
//    }
//}

void MainWindow::openImage(){
    if(isLoaded){
        horizontalSeamCarvingAction->setChecked(false);
        verticalSeamCarvingAction->setChecked(false);
        delete ui->operationDockWidget->widget();
        ui->operationDockWidget->setWidget(new QWidget);
    }
    QString filepath = QFileDialog::getOpenFileName(this, qAppName() + " - Choose image.", ".", "image(*.jpg *.png)");
    if(filepath == "")
        return;
    canvas->readImage(filepath);
    horizontalSeamCarvingAction->setEnabled(true);
    verticalSeamCarvingAction->setEnabled(true);
    isLoaded = true;
}

void MainWindow::showHorizontalSeamCarvingOperation(bool checked){
    if(checked){
        verticalSeamCarvingAction->setChecked(false);
        QWidget *widget = new SeamCarvingOperationWidget(nullptr, canvas, true);
        ui->operationDockWidget->setWidget(widget);
    }else{
        delete ui->operationDockWidget->widget();
        ui->operationDockWidget->setWidget(new QWidget);
    }
}


void MainWindow::showVerticalSeamCarvingOperation(bool checked){
    if(checked){
        horizontalSeamCarvingAction->setChecked(false);
        QWidget *widget = new SeamCarvingOperationWidget(nullptr, canvas, false);
        ui->operationDockWidget->setWidget(widget);
    }else{
        delete ui->operationDockWidget->widget();
        ui->operationDockWidget->setWidget(new QWidget);
    }
}
