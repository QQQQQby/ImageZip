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

    imageSaveAction = new QAction(QIcon(":/save"), "Save Image", this);
    imageSaveAction->setShortcut(QKeySequence::Save);
    imageSaveAction->setToolTip("Save current image.");
    connect(imageSaveAction, SIGNAL(triggered()), this, SLOT(saveImage()));

    imageCloseAction = new QAction(QIcon(":/close"), "Close Image", this);
    imageCloseAction->setShortcut(QKeySequence::Close);
    imageCloseAction->setToolTip("Close current image.");
    connect(imageCloseAction, SIGNAL(triggered()), this, SLOT(closeImage()));

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
    fileMenu->addSeparator();
    fileMenu->addAction(imageSaveAction);
    fileMenu->addAction(imageCloseAction);

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

    imageSaveAction->setEnabled(false);
    imageCloseAction->setEnabled(false);
    horizontalSeamCarvingAction->setEnabled(false);
    verticalSeamCarvingAction->setEnabled(false);
    state = INITIAL_STATE;
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::openImage(){
    QString filepath = QFileDialog::getOpenFileName(this, qAppName() + " - Choose image.", ".", "image(*.jpg *.png)");
    if(filepath == "")
        return;

    canvas->readImage(filepath);

    if(state == OPERATING_STATE){
        horizontalSeamCarvingAction->setChecked(false);
        verticalSeamCarvingAction->setChecked(false);
        delete ui->operationDockWidget->widget();
        ui->operationDockWidget->setWidget(new QWidget);
    }
    imageSaveAction->setEnabled(true);
    imageCloseAction->setEnabled(true);
    horizontalSeamCarvingAction->setEnabled(true);
    verticalSeamCarvingAction->setEnabled(true);
}

void MainWindow::saveImage(){
    QString filepath = QFileDialog::getSaveFileName(this, qAppName() + " - Save image.", ".", "image(*.png *.jpg)");
    if(filepath == "")
        return;
    canvas->saveImage(filepath);
}

void MainWindow::closeImage(){
    if(state == OPERATING_STATE){
        horizontalSeamCarvingAction->setChecked(false);
        verticalSeamCarvingAction->setChecked(false);
        delete ui->operationDockWidget->widget();
        ui->operationDockWidget->setWidget(new QWidget);
    }
    imageSaveAction->setEnabled(false);
    imageCloseAction->setEnabled(false);
    horizontalSeamCarvingAction->setEnabled(false);
    verticalSeamCarvingAction->setEnabled(false);
    canvas->clearImage();
    state = INITIAL_STATE;
}

void MainWindow::showHorizontalSeamCarvingOperation(bool checked){
    delete ui->operationDockWidget->widget();
    if(checked){
        verticalSeamCarvingAction->setChecked(false);
        QWidget *widget = new SeamCarvingOperationWidget(nullptr, canvas, true);
        ui->operationDockWidget->setWidget(widget);
        state = OPERATING_STATE;
    }else{
        ui->operationDockWidget->setWidget(new QWidget);
        state = IMAGE_LOADED_STATE;
    }
}


void MainWindow::showVerticalSeamCarvingOperation(bool checked){
    delete ui->operationDockWidget->widget();
    if(checked){
        horizontalSeamCarvingAction->setChecked(false);
        QWidget *widget = new SeamCarvingOperationWidget(nullptr, canvas, false);
        ui->operationDockWidget->setWidget(widget);
        state = OPERATING_STATE;
    }else{
        ui->operationDockWidget->setWidget(new QWidget);
        state = IMAGE_LOADED_STATE;
    }
}
