#include "node.h"

Node::Node()
{
    pos = QVector3D(0.0f, 0.0f, 0.0f);
}

Node::Node(int ID, QVector3D pos)
{
    this->ID = ID;
    this->pos = pos;
}

Node::Node(int ID, double x, double y, double z)
{
    this->ID = ID;
    this->pos[0] = x;
    this->pos[1] = y;
    this->pos[2] = z;
}

Node::~Node()
{

}

QVector3D Node::Position() const
{
    return this->pos;
}

int Node::GetID()
{
    return this->ID;
}
