#ifndef SIMPLEOBJECT3D_H
#define SIMPLEOBJECT3D_H

#include <QOpenGLBuffer>
#include <QMatrix4x4>
#include <QVector2D>
#include "transformational.h"

class QOpenGLTexture;
class QOpenGLFunctions;
class QOpenGLShaderProgram;
class Material;

struct VertexData{
    VertexData(){}

    VertexData(QVector3D p, QVector2D t,QVector3D n):
        position(p),texCoord(t),normal(n)
    {
    }
    QVector3D position;
    QVector2D texCoord;
    QVector3D normal;
    QVector3D tangent;
    QVector3D bitangent;
};

class SimpleObject3D : public Transformational {
public:
    SimpleObject3D();
    SimpleObject3D(const QVector<VertexData> &vertData,const QVector<GLuint> &indexes,Material *material);
    ~SimpleObject3D();
    void init(const QVector<VertexData> &vertData,const QVector<GLuint> &indexes,Material *material);

    void draw(QOpenGLShaderProgram *program, QOpenGLFunctions *function);
    void rotate(const QQuaternion &r);
    void translate(const QVector3D &t);
    void scale(const float &s);
    void setGlobalTransform(const QMatrix4x4 &g);

private:
    QOpenGLBuffer m_vertexBuffer; // буфер вершин
    QOpenGLBuffer m_indexBuffer;  // буфер индексов
    QOpenGLTexture *m_diffuseMap;    // текстура
    QOpenGLTexture *m_normalMap;    // карта нормалей

    QQuaternion m_rotate;         // врашение
    QVector3D m_translate;        // вектор переноса
    float m_scale;                // маштабирование
    QMatrix4x4 m_globalTransform; // хранит глобальное преобразование

    Material *m_material;
};

#endif // SIMPLEOBJECT3D_H
