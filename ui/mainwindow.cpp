#include "mainwindow.h"
#include "ui_mainwindow.h"

#include<QDebug>
#include<QFileDialog>
#include<QVBoxLayout>
#include<QSlider>

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
    imageOpenAction->setToolTip("Run horizontal Seam Carving.");
    seamCarvingAction->setCheckable(true);
    connect(seamCarvingAction, SIGNAL(triggered(bool)), this, SLOT(showHSeamCarvingOperation(bool)));

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

    isLoaded = false;
    seamCarvingAction->setEnabled(false);
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

    }
    QString filepath = QFileDialog::getOpenFileName(this, qAppName() + " - Choose image.", ".", "image(*.jpg *.png)");
    if(filepath == "")
        return;
    canvas->readImage(filepath);

//    canvas->setMinimumSize(scrollArea->width()-2, scrollArea->height()-2);
    seamCarvingAction->setEnabled(true);
    isLoaded = true;
}

void MainWindow::showHSeamCarvingOperation(bool checked){
    qDebug()<<"check seam carving:"<<checked;
    if(checked){
        QWidget *widget = new QWidget;
        QVBoxLayout *layout = new QVBoxLayout;

        QSlider *slider = new QSlider(widget);
        slider->setOrientation(Qt::Horizontal);
        slider->setMinimum(1);
        slider->setMaximum(canvas->getImageWidth());
        slider->setSingleStep(1);
        connect(slider, SIGNAL(valueChanged(int)), this, SLOT(setHSeamCarvingValue(int)));

        layout->addWidget(slider);
        layout->addStretch();
        widget->setLayout(layout);
        ui->operationDockWidget->setWidget(widget);
    }else{
        delete ui->operationDockWidget->widget();
        ui->operationDockWidget->setWidget(new QWidget);
    }
}

void MainWindow::setHSeamCarvingValue(int value){
    qDebug() << value;
}
