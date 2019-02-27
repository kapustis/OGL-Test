#ifndef WIDGET_H
#define WIDGET_H

#include <QOpenGLWidget>
#include <QMatrix4x4>
#include <QOpenGLShaderProgram>
#include <QOpenGLTexture>
#include <QOpenGLBuffer>
#include <QBasicTimer>

class ObjectEngine3D;
class Transformational;
class Group3D;
class Camera3D;
class SkyBox;
class QOpenGLFramebufferObject;
class Light;

class Widget : public QOpenGLWidget{
    Q_OBJECT

public:
    Widget(QWidget *parent = 0);
    ~Widget();

protected:
    void initializeGL();
    void resizeGL(int w,int h);
    void paintGL();

    void mousePressEvent(QMouseEvent *event);
    void mouseMoveEvent(QMouseEvent *event);
    void keyPressEvent(QKeyEvent *event);
    void wheelEvent(QWheelEvent *event);
    void timerEvent(QTimerEvent *event);

    void initShaders();
    void initCube(float width, float heigth, float depth, QImage *pathDiffuseMap = 0, QImage *pathNormalMap = 0);


private:
    QMatrix4x4 m_projectionMatrix;
    QMatrix4x4 m_projectionLightMatrix;

    QOpenGLShaderProgram m_program;
    QOpenGLShaderProgram m_programSkyBox;
    QOpenGLShaderProgram m_programDepth;
    QVector2D m_mousePosition;

    QVector<ObjectEngine3D *> m_objects;
    QVector<Group3D *> m_groups;
    QVector<Transformational *> m_TransformObjects;

    QBasicTimer m_timer;

    float angleObject;
    float angleGroup1;
    float angleGroup2;
    float angleMain;

    Camera3D *m_camera;
    SkyBox *m_skybox;

    QOpenGLFramebufferObject *m_depthBuffer;
    qint32 m_fbHeight;
    qint32 m_fbWidth;
    float sizeShadow = 9216.0;

    Light *m_light0[3];
};

#endif // WIDGET_H
