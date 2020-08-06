#include "beamcolumnelement.h"

BeamColumnElement::BeamColumnElement()
{

}

BeamColumnElement::BeamColumnElement(int ID, Node n1, Node n2)
{
    this->ID = ID;
    this->n1 = n1;
    this->n2 = n2;
}

BeamColumnElement::~BeamColumnElement()
{

}

Node BeamColumnElement::GetFirstNode()
{
    return this->n1;
}

Node BeamColumnElement::GetSecondNode()
{
    return this->n2;
}

int BeamColumnElement::GetID()
{
    return this->ID;
}
