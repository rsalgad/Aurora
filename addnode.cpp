#include "addnode.h"
#include "ui_addNode.h"
#include "node.h"

addNode::addNode(QWidget *parent, int index) :
    QDialog(parent),
    ui(new Ui::addNode)
{
    this->mainWindow = (MainWindow*)parent;
    ui->setupUi(this);
    this->index = index;
    if (index != -1){
        QVector3D nodePos = mainWindow->GetStructureManager()->GetNodeVector()->at(index).Position();

        ui->txt_XCoord->setText(QString::number(nodePos.x()));
        ui->txt_YCoord->setText(QString::number(nodePos.y()));
        ui->txt_ZCoord->setText(QString::number(nodePos.z()));
    }
}

addNode::~addNode()
{
    delete ui;
}

void addNode::on_pushButton_clicked()
{
    StructureManager* man = mainWindow->GetStructureManager();
    if (man->GetNodeVector()->size() == 0){
        mainWindow->AddRoot("Nodes");
    }

    double x = ui->txt_XCoord->toPlainText().toDouble();
    double y = ui->txt_YCoord->toPlainText().toDouble();
    double z = ui->txt_ZCoord->toPlainText().toDouble();

    Node n(man->GetNodeVector()->size()+1,x, y, z);

    if (index != -1){
        man->EditNode(index, n);
    } else{
        man->AddNode(n);
        mainWindow->AddChild(mainWindow->GetTreeWidgetItem("Nodes"), "Node " + QString::number(man->GetNodeVector()->size()));
    }

}
