#ifndef BEAMCOLUMNELEMENT_H
#define BEAMCOLUMNELEMENT_H
#include "node.h"

class BeamColumnElement
{
public:
    BeamColumnElement();
    BeamColumnElement(int ID, Node n1, Node n2);
    ~BeamColumnElement();
    Node GetFirstNode();
    Node GetSecondNode();
    int GetID();

private:
    Node n1;
    Node n2;
    int ID;
};

#endif // BEAMCOLUMNELEMENT_H
