#ifndef STRUCTUREMANAGER_H
#define STRUCTUREMANAGER_H
#include <QVector>
#include "node.h"
#include "beamcolumnelement.h"
#include "myqopenglwidget.h"

class StructureManager
{
public:
    StructureManager();
    StructureManager(myQOpenGLWidget* widget);
    void AddNode(Node n);
    void EditNode(int nodeIndex, Node n);
    void AddBeamColumnElement(BeamColumnElement e);
    void EditBeamColumnElement(int eleIndex, BeamColumnElement e);
    QVector<Node>* GetNodeVector();
    QVector<BeamColumnElement>* GetBeamColumnVector();

private:
    QVector<Node> nodeVector;
    QVector<BeamColumnElement> bcVector;
    myQOpenGLWidget* widget;
};

#endif // STRUCTUREMANAGER_H
