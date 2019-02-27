#include "camera3d.h"
#include <QOpenGLShaderProgram>

Camera3D::Camera3D(){
    m_scale = 1.0f;
    m_globalTransform.setToIdentity();
}

void Camera3D::draw(QOpenGLShaderProgram *program, QOpenGLFunctions *function){
    if(function != 0) return;

    program->setUniformValue("u_viewMatrix",m_viewMatrix);
}

void Camera3D::rotate(const QQuaternion &r){
    m_rotate = r * m_rotate;

    updateVM();
}

void Camera3D::rotateX(const QQuaternion &r){
    m_rotateX = r * m_rotateX;
    m_rotate =   m_rotateX * m_rotateY;
    updateVM();
}

void Camera3D::rotateY(const QQuaternion &r){
    m_rotateY = r * m_rotateY;
    m_rotate =  m_rotateX * m_rotateY;
    updateVM();
}

void Camera3D::translate(const QVector3D &t){
    m_translate += t ;

    updateVM();
}

void Camera3D::scale(const float &s){
    m_scale *= s;

    updateVM();
}

void Camera3D::setGlobalTransform(const QMatrix4x4 &g){
    m_globalTransform = g;

    updateVM();
}

const QMatrix4x4 &Camera3D::getVM() const{
    return m_viewMatrix;
}

void Camera3D::updateVM(){
    m_viewMatrix.setToIdentity();
    m_viewMatrix.translate(m_translate);
    m_viewMatrix.rotate(m_rotate);
    m_viewMatrix.scale(m_scale);
    m_viewMatrix = m_viewMatrix *  m_globalTransform.inverted();
}




