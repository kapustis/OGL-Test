#ifndef SKYBOX_H
#define SKYBOX_H

#include "transformational.h"

class SimpleObject3D;
class QImage;

class SkyBox : public Transformational{
public:
    SkyBox(float width,const QImage &texture);
    ~SkyBox();
    // Transformational interface
    void rotate(const QQuaternion &r);
    void translate(const QVector3D &t);
    void scale(const float &s);
    void setGlobalTransform(const QMatrix4x4 &g);
    void draw(QOpenGLShaderProgram *program, QOpenGLFunctions *function);
private:
    SimpleObject3D *m_cube;
protected:
};

#endif // SKYBOX_H
