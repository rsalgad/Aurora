#ifndef MYQOPENGLWIDGET_H
#define MYQOPENGLWIDGET_H
#include <QOpenGLWidget>
#include <QOpenGLShaderProgram>
#include <QInputEvent>
#include <QOpenGLBuffer>
#include "node.h"
#include "beamcolumnelement.h"

class myQOpenGLWidget : public QOpenGLWidget
{
    Q_OBJECT
public:
    myQOpenGLWidget(QWidget *parent);
    ~myQOpenGLWidget();
    void UpdatedPointVector(QVector<Node> v);
    void UpdateLineVector(QVector<BeamColumnElement> v);
    QSize sizeHint() const;

protected:
    void initializeGL();
    void resizeGL(int width, int height);
    void paintGL();
    void mousePressEvent(QMouseEvent *event);
    void mouseMoveEvent(QMouseEvent *event);
    void wheelEvent(QWheelEvent *event);

private:
    void UpdateAverageView();
    void UpdateNodeBuffer();
    void UpdateElementBuffer();

    QMatrix4x4 pMatrix;
    QOpenGLShaderProgram shaderProgram;
    QVector<QVector3D> nodes;
    QVector<QVector3D> elementNodes;
    QVector<int> nodeIndices;
    QVector<int> elementIndices;
    QVector<QVector3D> nodeColors;
    QVector<QVector3D> elementColors;
    QVector3D averageView;
    double alpha;
    double beta;
    double distance;
    QPoint lastMousePosition;
    QOpenGLBuffer nodeBuffer;
    QOpenGLBuffer elementBuffer;
    double orthoSize;
    double aspectRatioHW;
    double aspectRatioWH;
};

#endif // MYQOPENGLWIDGET_H
