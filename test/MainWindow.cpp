#include "MainWindow.h"
#include "ui_MainWindow.h"
#include "qgraphicsblock.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow),
    m_scene(this)
{
    ui->setupUi(this);
    m_scene.setSceneRect(-1000, -1000, 2000, 2000);
    ui->graphicsView->setScene(&m_scene);
    QGraphicsBlock *block1 = new QGraphicsBlock(this);
    block1->setId(1);
    connect(block1, SIGNAL(inputClicked(int)),
            this, SLOT(inputClicked(int)));
    connect(block1, SIGNAL(outputClicked(int)),
            this, SLOT(outputClicked(int)));
    QGraphicsBlock *block2 = new QGraphicsBlock(this);
    block2->setId(2);
    connect(block2, SIGNAL(inputClicked(int)),
            this, SLOT(inputClicked(int)));
    connect(block2, SIGNAL(outputClicked(int)),
            this, SLOT(outputClicked(int)));
    m_scene.addItem(block1);
    block1->setPos(0, 0);
    m_scene.addItem(block2);
    block2->setPos(100, 100);
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::inputClicked(int id)
{
    QGraphicsBlock *block = (QGraphicsBlock *)sender();

}

void MainWindow::outputClicked(int id)
{
    QGraphicsBlock *block = (QGraphicsBlock *)sender();
}
