#include "group3d.h"

#include <QMatrix4x4>

Group3D::Group3D(){
    m_scale = 1.0f;
}
void Group3D::draw(QOpenGLShaderProgram *program, QOpenGLFunctions *function){
    for (int i = 0; i < m_objects.size(); ++i)
        m_objects[i]->draw(program,function);
}

void Group3D::rotate(const QQuaternion &r){
    m_rotate = r * m_rotate;

    QMatrix4x4 localMatrix;
    localMatrix.setToIdentity();
    localMatrix.translate(m_translate);
    localMatrix.rotate(m_rotate);
    localMatrix.scale(m_scale);
    localMatrix = m_globalTransform * localMatrix;

    for (int i = 0; i < m_objects.size(); ++i){
        m_objects[i]->setGlobalTransform(localMatrix);
    }
}

void Group3D::translate(const QVector3D &t){
    m_translate += t ;

    QMatrix4x4 localMatrix;
    localMatrix.setToIdentity();
    localMatrix.translate(m_translate);
    localMatrix.rotate(m_rotate);
    localMatrix.scale(m_scale);
    localMatrix = m_globalTransform *localMatrix;

    for (int i = 0; i < m_objects.size(); ++i){
        m_objects[i]->setGlobalTransform(localMatrix);
    }
}

void Group3D::scale(const float &s){
    m_scale *= s;

    QMatrix4x4 localMatrix;
    localMatrix.setToIdentity();
    localMatrix.translate(m_translate);
    localMatrix.rotate(m_rotate);
    localMatrix.scale(m_scale);
    localMatrix = m_globalTransform *localMatrix;

    for (int i = 0; i < m_objects.size(); ++i){
        m_objects[i]->setGlobalTransform(localMatrix);
    }
}

void Group3D::setGlobalTransform(const QMatrix4x4 &g){
    m_globalTransform = g;

    QMatrix4x4 localMatrix;
    localMatrix.setToIdentity();
    localMatrix.translate(m_translate);
    localMatrix.rotate(m_rotate);
    localMatrix.scale(m_scale);
    localMatrix = m_globalTransform *localMatrix;

    for (int i = 0; i < m_objects.size(); ++i){
        m_objects[i]->setGlobalTransform(localMatrix);
    }

}

void Group3D::addObject(Transformational *obj){
    m_objects.append(obj);

    QMatrix4x4 localMatrix;
    localMatrix.setToIdentity();
    localMatrix.translate(m_translate);
    localMatrix.rotate(m_rotate);
    localMatrix.scale(m_scale);
    localMatrix = m_globalTransform *localMatrix;

    m_objects[m_objects.size() - 1]->setGlobalTransform(localMatrix);
}

void Group3D::delObject(Transformational *obj){
    m_objects.removeAll(obj);
}

void Group3D::delObject(const int &index){
    m_objects.remove(index);
}
