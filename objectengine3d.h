#ifndef OBJECTENGINE3D_H
#define OBJECTENGINE3D_H

#include <QVector>
#include "transformational.h"

#include "simpleobject3d.h"
#include "materiallibrary.h"

class ObjectEngine3D : public Transformational{
public:
    ObjectEngine3D();
    void loadObjectFromFile(const QString &filename);
    void addObject(SimpleObject3D *object);
    SimpleObject3D *getObject(quint32 index);
    void calculateTBN(QVector<VertexData> &vertData);
    // Transformational interface
    void rotate(const QQuaternion &r);
    void translate(const QVector3D &t);
    void scale(const float &s);
    void setGlobalTransform(const QMatrix4x4 &g);
    void draw(QOpenGLShaderProgram *program, QOpenGLFunctions *function);
private:
    QVector<SimpleObject3D *> m_objects;
    MaterialLibrary m_materialLibrary;    
};

#endif // OBJECTENGINE3D_H
