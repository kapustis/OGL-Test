#ifndef TRANSFORMATIONAL_H
#define TRANSFORMATIONAL_H

class QMatrix4x4;
class QQuaternion;
class QVector3D;
class QOpenGLShaderProgram;
class QOpenGLFunctions;


class Transformational{
public:
    virtual ~Transformational(){}
    virtual void rotate(const QQuaternion &r) = 0;
    virtual void translate(const QVector3D &t) = 0;
    virtual void scale(const float &s) = 0;
    virtual void setGlobalTransform(const QMatrix4x4 &g) = 0;
    virtual void draw(QOpenGLShaderProgram *program, QOpenGLFunctions *function) = 0;
};


#endif // TRANSFORMATIONAL_H
