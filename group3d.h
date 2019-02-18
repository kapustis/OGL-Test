#ifndef GROUP3D_H
#define GROUP3D_H

#include "transformational.h"
#include <QMatrix4x4>
#include <QQuaternion>
#include <QVector>
#include <QVector3D>

class Group3D : public Transformational{
public:
    Group3D();
    void rotate(const QQuaternion &r);
    void translate(const QVector3D &t);
    void scale(const float &s);
    void setGlobalTransform(const QMatrix4x4 &g);
    void draw(QOpenGLShaderProgram *program, QOpenGLFunctions *function);

    void addObject(Transformational *obj);
    void delObject(Transformational *obj);
    void delObject(const int &index);
private:
    QQuaternion m_rotate;
    QVector3D m_translate;
    float m_scale;                // маштабирование
    QMatrix4x4 m_globalTransform; // хранит глобальное преобразование

    QVector<Transformational *> m_objects;
};

#endif // GROUP3D_H
