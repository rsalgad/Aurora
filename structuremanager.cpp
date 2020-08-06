#include "structuremanager.h"

StructureManager::StructureManager()
{

}

StructureManager::StructureManager(myQOpenGLWidget *widget)
{
    this->widget = widget;
}

void StructureManager::AddNode(Node n)
{
    this->nodeVector.append(n);
    widget->UpdatedPointVector(this->nodeVector);
    widget->update();
}

void StructureManager::EditNode(int nodeIndex, Node n)
{
    this->nodeVector[nodeIndex] = n;
    widget->UpdatedPointVector(this->nodeVector);
    widget->update();
}

void StructureManager::AddBeamColumnElement(BeamColumnElement e)
{
    this->bcVector.append(e);
    widget->UpdateLineVector(this->bcVector);
    widget->update();
}

void StructureManager::EditBeamColumnElement(int eleIndex, BeamColumnElement e)
{
    this->bcVector[eleIndex] = e;
    widget->UpdateLineVector(this->bcVector);
    widget->update();
}

QVector<Node> *StructureManager::GetNodeVector()
{
    return &this->nodeVector;
}

QVector<BeamColumnElement> *StructureManager::GetBeamColumnVector()
{
    return &this->bcVector;
}
