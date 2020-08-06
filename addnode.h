#ifndef ADDNODE_H
#define ADDNODE_H

#include <QDialog>
#include "structuremanager.h"
#include "mainwindow.h"

namespace Ui {
class addNode;
}

class addNode : public QDialog
{
    Q_OBJECT

public:
    explicit addNode(QWidget *parent = nullptr, int index = -1);
    ~addNode();

private slots:
    void on_pushButton_clicked();

private:
    Node* node;
    int index;
    MainWindow* mainWindow;
    Ui::addNode *ui;
};

#endif // ADDNODE_H
