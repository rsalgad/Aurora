#include "addbeamcolumnelement.h"
#include "ui_addbeamcolumnelement.h"

addBeamColumnElement::addBeamColumnElement(QWidget *parent, int index) :
    QDialog(parent),
    ui(new Ui::addBeamColumnElement)
{
    this->mainWindow = (MainWindow*)parent;
    ui->setupUi(this);

    this->index = index;
    if (index != -1){
        BeamColumnElement ele = mainWindow->GetStructureManager()->GetBeamColumnVector()->at(index);

        ui->txt_n1->setText(QString::number(ele.GetFirstNode().GetID()));
        ui->txt_n2->setText(QString::number(ele.GetFirstNode().GetID()));
    }
}

addBeamColumnElement::~addBeamColumnElement()
{
    delete ui;
}

void addBeamColumnElement::on_pushButton_clicked()
{
    StructureManager* man = mainWindow->GetStructureManager();
    if (man->GetBeamColumnVector()->size() == 0){
        mainWindow->AddRoot("Beam Column Elements");
    }

    int n1 = ui->txt_n1->toPlainText().toInt();
    int n2 = ui->txt_n2->toPlainText().toInt();

    man->AddBeamColumnElement(BeamColumnElement(man->GetBeamColumnVector()->size() + 1, man->GetNodeVector()->at(n1-1), man->GetNodeVector()->at(n2-1)));

    mainWindow->AddChild(mainWindow->GetTreeWidgetItem("Beam Column Elements"), "Element " + QString::number(man->GetBeamColumnVector()->size()));
}
