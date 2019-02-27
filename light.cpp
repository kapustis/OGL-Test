#include "light.h"
#include  <QtMath>

Light::Light(const Type &type):
    m_amdienceColor(1.0f,1.0f,1.0f),
    m_diffuseColor(1.0f,1.0f,1.0f),
    m_specularColor(1.0f,1.0f,1.0f),
    m_position(0.0f,0.0f,0.0f,1.0f),
    m_direction(0.0f,0.0f,-1.0f,0.0f),
    m_cutoff(M_PI_2),
    m_type(type)
{
    m_lightMatrix.setToIdentity();
    m_lightMatrix.lookAt(m_position.toVector3D(),
                         (m_position + m_direction).toVector3D(),
                         QVector3D(m_direction.x(), m_direction.z(), -m_direction.y())
                         );
}

void Light::setAmbienseColor(const QVector3D &ambienseColor){
    m_amdienceColor = ambienseColor;
}
const QVector3D &Light::getAmbienseColor() const{
    return m_amdienceColor;
}

void Light::setDiffuseColor(const QVector3D &diffuseColor){
    m_diffuseColor = diffuseColor;
}
const QVector3D &Light::getDiffuseColor() const{
    return m_diffuseColor;
}

void Light::setSpecularColor(const QVector3D &specularColor){
    m_specularColor = specularColor;
}
const QVector3D &Light::getSpecularColor() const{
    return m_specularColor;
}

void Light::setPosition(const QVector4D &position){
    m_position = position;
    m_lightMatrix.setToIdentity();
    m_lightMatrix.lookAt(m_position.toVector3D(),
                         (m_position + m_direction).toVector3D(),
                         QVector3D(m_direction.x(), m_direction.z(), -m_direction.y())
                         );
}
const QVector4D &Light::getPosition() const{
    return m_position;
}

void Light::setDirection(const QVector4D &direction){
    m_direction = direction.normalized();
    m_lightMatrix.setToIdentity();
    m_lightMatrix.lookAt(m_position.toVector3D(),
                         (m_position + m_direction).toVector3D(),
                         QVector3D(m_direction.x(), m_direction.z(), -m_direction.y())
                         );
}
const QVector4D &Light::getDirection() const{
    return m_direction;
}

void Light::setCutoff(const float &cutoff){
    m_cutoff = cutoff;
}
const float &Light::getCutoff() const{
    return m_cutoff;
}

void Light::setType(const Light::Type &type){
    m_type = type;
}
const Light::Type &Light::getType() const{
    return m_type;
}

const QMatrix4x4 &Light::getLightMatrix() const{
    return m_lightMatrix;
}
