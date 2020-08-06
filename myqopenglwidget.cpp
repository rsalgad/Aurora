#include "myqopenglwidget.h"
#include <QVector3D>
#include <QDir>
#include <QOpenGLFunctions>
#include <QInputEvent>

myQOpenGLWidget::myQOpenGLWidget(QWidget *parent) : QOpenGLWidget(parent)
{
    alpha = 25;
    beta = -25;
    distance = 50;
    orthoSize = 1;
    averageView = QVector3D(0,0,0);
}

myQOpenGLWidget::~myQOpenGLWidget()
{

}

void myQOpenGLWidget::UpdatedPointVector(QVector<Node> v)
{
    nodeColors = QVector<QVector3D>(v.size(), QVector3D(0,0,0));
    this->nodes.clear();
    for (int i = 0; i < v.size(); i++){
        this->nodes.append(v[i].Position());
    }
    UpdateNodeBuffer();
}

void myQOpenGLWidget::UpdateLineVector(QVector<BeamColumnElement> v)
{
    elementColors = QVector<QVector3D>(v.size() * 2, QVector3D(1,0,0));
    this->elementNodes.clear();
    for (int i = 0; i < v.size(); i++){
        this->elementNodes.append(v[i].GetFirstNode().Position());
        this->elementNodes.append(v[i].GetSecondNode().Position());
    }
    UpdateElementBuffer();
}

QSize myQOpenGLWidget::sizeHint() const
{
    //return QSize(640, 480);
    return QSize();
}

void myQOpenGLWidget::initializeGL()
{
    QOpenGLFunctions* f = QOpenGLContext::currentContext()->functions();
    f->glEnable(GL_DEPTH_TEST);
    f->glEnable(GL_CULL_FACE); //disable this for double-sided triangles?
    f->glHint(GL_LINE_SMOOTH_HINT, GL_NICEST);
    f->glEnable(GL_LINE_SMOOTH);
    f->glEnable(GL_MULTISAMPLE);
    f->glLineWidth(3.0);
    //f->glHint(GL_POINT_SMOOTH_HINT, GL_NICEST);
    //f->glEnable(GL_POINT_SMOOTH);
    f->glEnable(GL_PROGRAM_POINT_SIZE);
    f->glLineWidth(3.0);
    f->glClearColor(1,1,1,1); //black?

    shaderProgram.addShaderFromSourceFile(QOpenGLShader::Vertex,":/resources/shaders/vertexShader.vsh");
    shaderProgram.addShaderFromSourceFile(QOpenGLShader::Fragment, ":/resources/shaders/fragmentShader.fsh");
    shaderProgram.link();

}

void myQOpenGLWidget::resizeGL(int width, int height)
{
    if (height == 0) {
    height = 1;
    }
    aspectRatioHW = (double)height / (double)width;
    aspectRatioWH = (double)width / (double)height;
    //pMatrix.setToIdentity();
    //pMatrix.ortho(size * -1.0f,size * 1.0f, size * -1.0f, size * 1.0f, 0.001, 1000);
    //pMatrix.perspective(60.0, (float) width / (float) height, 0.001, 1000);

    QOpenGLFunctions* f = QOpenGLContext::currentContext()->functions();
    f->glViewport(0, 0, width, height);
}

void myQOpenGLWidget::paintGL()
{
    QOpenGLFunctions* f = QOpenGLContext::currentContext()->functions();
    f->glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    QMatrix4x4 mMatrix;
    QMatrix4x4 vMatrix;

    pMatrix.setToIdentity();
    pMatrix.ortho(orthoSize * -1.0f,orthoSize * 1.0f, orthoSize * -1.0f * aspectRatioHW, orthoSize * 1.0f * aspectRatioHW, 0.1, 10000);
    QMatrix4x4 cameraTransformation;
    cameraTransformation.rotate(alpha, 0, 1, 0);
    cameraTransformation.rotate(beta, 1, 0, 0);
    QVector3D cameraPosition = cameraTransformation * QVector3D(0, 0, distance);
    QVector3D cameraUpDirection = cameraTransformation * QVector3D(0, 1, 0);
    vMatrix.lookAt(cameraPosition, averageView, cameraUpDirection);

    if(elementNodes.size() != 0){
        shaderProgram.bind();
        shaderProgram.setUniformValue("mvpMatrix", pMatrix * vMatrix * mMatrix);

        elementBuffer.bind();
        int offsetElement = 0;
        shaderProgram.setAttributeBuffer("vertex", GL_FLOAT, offsetElement, 3, 0);
        shaderProgram.enableAttributeArray("vertex");
        offsetElement += elementNodes.size() * 3 * sizeof(GLfloat);
        shaderProgram.setAttributeBuffer("color", GL_FLOAT, offsetElement, 3, 0);
        shaderProgram.enableAttributeArray("color");
        elementBuffer.release();

        f->glDrawArrays(GL_LINES, 0, elementNodes.size());

        shaderProgram.disableAttributeArray("vertex");
        shaderProgram.disableAttributeArray("color");
        shaderProgram.release();
    }


    if(nodes.size() != 0){
        shaderProgram.bind();
        shaderProgram.setUniformValue("mvpMatrix", pMatrix * vMatrix * mMatrix);

        nodeBuffer.bind();
        int offsetNode = 0;
        shaderProgram.setAttributeBuffer("vertex", GL_FLOAT, offsetNode, 3, 0);
        shaderProgram.enableAttributeArray("vertex");
        offsetNode += nodes.size() * 3 * sizeof(GLfloat);
        shaderProgram.setAttributeBuffer("color", GL_FLOAT, offsetNode, 3, 0);
        shaderProgram.enableAttributeArray("color");
        nodeBuffer.release();

        f->glDrawArrays(GL_POINTS, 0, nodes.size());

        shaderProgram.disableAttributeArray("vertex");
        shaderProgram.disableAttributeArray("color");
        shaderProgram.release();
    }

}

void myQOpenGLWidget::mousePressEvent(QMouseEvent *event)
{
    lastMousePosition = event->pos();
    event->accept();
}

void myQOpenGLWidget::mouseMoveEvent(QMouseEvent *event)
{
    int deltaX = event->x() - lastMousePosition.x();
    int deltaY = event->y() - lastMousePosition.y();
    if (event->buttons() & Qt::RightButton) {
        alpha -= deltaX;
        while (alpha < 0) {
            alpha += 360;
        }

        while (alpha >= 360) {
            alpha -= 360;
        }

        beta -= deltaY;
        if (beta < -90) {
            beta = -90;
        }

        if (beta > 90) {
            beta = 90;
        }
        update();
        }
    lastMousePosition = event->pos();
    event->accept();
}

void myQOpenGLWidget::wheelEvent(QWheelEvent *event)
{
    int delta = event->delta();
    if (event->orientation() == Qt::Vertical) {
        if (delta < 0) {
            //distance *= 1.1;
            orthoSize *=1.1;
        } else if (delta > 0) {
            //distance *= 0.9;
            orthoSize *=0.9;
        }

        update();
    }
    event->accept();
}

void myQOpenGLWidget::UpdateAverageView()
{
    double maxX = 0, maxY = 0, minX = 0, minY = 0, maxZ = 0, minZ = 0;
    for (int i = 0; i < nodes.size(); i++){
        if (nodes[i].x() > maxX){
            maxX = nodes[i].x();
        } else if (nodes[i].x() < minX){
            minX = nodes[i].x();
        }
        if (nodes[i].y() > maxY){
            maxY = nodes[i].y();
        } else if(nodes[i].y() < minY){
            minY = nodes[i].y();
        }
        if (nodes[i].z() > maxZ){
            maxZ = nodes[i].z();
        } else if(nodes[i].z() < minZ){
            minZ = nodes[i].z();
        }
    }
    QVector3D v((maxX - minX) / 2, (maxY - minY)/2, (maxZ - minZ)/2);
    averageView = v;
}

void myQOpenGLWidget::UpdateNodeBuffer()
{
    UpdateAverageView();
    if (nodeBuffer.isCreated()){
        nodeBuffer.destroy();
    }

    nodeBuffer.create();
    nodeBuffer.bind();
    nodeBuffer.allocate(nodes.size() * (3 + 3) * sizeof(GLfloat));

    int offset = 0;
    nodeBuffer.write(offset, nodes.constData(), nodes.size() * 3 * sizeof(GLfloat));
    offset += nodes.size() * 3 * sizeof(GLfloat);
    nodeBuffer.write(offset, nodeColors.constData(), nodes.size() * 3 * sizeof(GLfloat));
    nodeBuffer.release();
}

void myQOpenGLWidget::UpdateElementBuffer()
{
    if (elementBuffer.isCreated()){
        elementBuffer.destroy();
    }

    elementBuffer.create();
    elementBuffer.bind();
    elementBuffer.allocate(elementNodes.size() * (3 + 3) * sizeof(GLfloat));

    int offset = 0;
    elementBuffer.write(offset, elementNodes.constData(), elementNodes.size() * 3 * sizeof(GLfloat));
    offset += elementNodes.size() * 3 * sizeof(GLfloat);
    elementBuffer.write(offset, elementColors.constData(), elementNodes.size() * 3 * sizeof(GLfloat));
    elementBuffer.release();
}

