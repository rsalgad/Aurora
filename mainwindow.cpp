#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "myqopenglwidget.h"
#include "addnode.h"
#include "addbeamcolumnelement.h"
#include "structuremanager.h"
#include <QVector3D>
#include <QtGui>
#include <QtCore>
#include <QOpenGLWidget>
#include <QOpenGLFunctions>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    QSurfaceFormat format;
    format.setSamples(8);
    ui->myOpenGLWidget->setFormat(format);
    structMan = StructureManager(ui->myOpenGLWidget);
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::AddRoot(QString name)
{
    QTreeWidgetItem *item = new QTreeWidgetItem();
    item->setText(0, name);
    ui->treeWidget->addTopLevelItem(item);
}

void MainWindow::AddChild(QTreeWidgetItem *parent, QString name)
{
    QTreeWidgetItem *item = new QTreeWidgetItem();
    item->setText(0, name);
    parent->addChild(item);
}

QTreeWidgetItem* MainWindow::GetTreeWidgetItem(QString name)
{
    QList<QTreeWidgetItem*> clist = ui->treeWidget->findItems(name, Qt::MatchContains|Qt::MatchRecursive, 0);
    return clist[0];
}

StructureManager *MainWindow::GetStructureManager()
{
    return &this->structMan;
}

void MainWindow::on_pushButton_clicked()
{
    addNode* w = new addNode(this);
    w->show();
}

void MainWindow::on_pushButton_2_clicked()
{
    addBeamColumnElement* w = new addBeamColumnElement(this);
    w->show();
}

void MainWindow::on_treeWidget_itemDoubleClicked(QTreeWidgetItem *item, int column)
{
    if (item->text(column).contains("Node")){
        QTreeWidgetItem* itm = GetTreeWidgetItem("Nodes");
        int index = itm->indexOfChild(item);
        addNode* w = new addNode(this, index);
        w->show();
    } else if (item->text(column).contains("Element")){
        QTreeWidgetItem* itm = GetTreeWidgetItem("Beam Column Elements");
        int index = itm->indexOfChild(item);
        addBeamColumnElement* w = new addBeamColumnElement(this, index);
        w->show();
    }
}
