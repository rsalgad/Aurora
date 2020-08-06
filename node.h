#ifndef NODE_H
#define NODE_H
#include <QVector3D>

class Node
{
public:
    Node();
    Node(int ID, QVector3D pos);
    Node(int ID, double x, double y, double z);
    ~Node();
    QVector3D Position() const;
    int GetID();

private:
    QVector3D pos;
    int ID;
};

#endif // NODE_H
