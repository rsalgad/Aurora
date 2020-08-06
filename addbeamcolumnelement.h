#ifndef ADDBEAMCOLUMNELEMENT_H
#define ADDBEAMCOLUMNELEMENT_H

#include <QDialog>
#include "structuremanager.h"
#include "mainwindow.h"

namespace Ui {
class addBeamColumnElement;
}

class addBeamColumnElement : public QDialog
{
    Q_OBJECT

public:
    explicit addBeamColumnElement(QWidget *parent = nullptr, int index = -1);
    ~addBeamColumnElement();

private slots:
    void on_pushButton_clicked();

private:
    Ui::addBeamColumnElement *ui;
    int index;
    MainWindow* mainWindow;
};

#endif // ADDBEAMCOLUMNELEMENT_H
