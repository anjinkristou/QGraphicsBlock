#include "MainWindow.h"
#include "ui_MainWindow.h"
#include "qgraphicsblock.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    ui->graphicsView->setScene(&m_scene);
    QGraphicsBlock *block = new QGraphicsBlock(this);
    m_scene.addItem(block);
    block->setPos(0, 0);
}

MainWindow::~MainWindow()
{
    delete ui;
}
