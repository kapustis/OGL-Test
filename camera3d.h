#ifndef CAMERA3D_H
#define CAMERA3D_H

#include "transformational.h"
#include <QMatrix4x4>
#include <QQuaternion>
#include <QVector3D>


class Camera3D : public Transformational{
public:
    Camera3D();
    // Transformational interface
    void draw(QOpenGLShaderProgram *program, QOpenGLFunctions *function = 0);
    void rotate(const QQuaternion &r);
    void rotateX(const QQuaternion &r);
    void rotateY(const QQuaternion &r);
    void translate(const QVector3D &t);
    void scale(const float &s);
    void setGlobalTransform(const QMatrix4x4 &g);

    const QMatrix4x4 &getVM() const;

    void updateVM();
private:
    QQuaternion m_rotate;
    QQuaternion m_rotateX;
    QQuaternion m_rotateY;
    QVector3D m_translate;
    float m_scale;                // маштабирование
    QMatrix4x4 m_globalTransform; // хранит глобальное преобразование

    //    QVector<Transformational *> m_objects;
    QMatrix4x4 m_viewMatrix;


};

#endif // CAMERA3D_H
