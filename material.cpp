#include "material.h"
#include <QImage>

Material::Material(){
     m_isUsingDiffuseMap = false;
     m_isUsingNormalMap = false;
}

void Material::setName(const QString &mtlName){
    m_mtlName = mtlName;
}
const QString &Material::mtlName() const{
    return m_mtlName;
}

void Material::setDiffuseColor(const QVector3D &diffuseColor){
    m_diffuseColor = diffuseColor;
}
const QVector3D &Material::diffuseColor() const{
    return m_diffuseColor;
}

void Material::setAmbientceColor(const QVector3D &ambientceColor){
    m_ambientceColor = ambientceColor;
}
const QVector3D &Material::ambientceColor() const{
    return m_ambientceColor;
}

void Material::setSpecularColor(const QVector3D &specularColor){
    m_specularColor = specularColor;
}
const QVector3D &Material::specularColor() const{
    return m_specularColor;
}

void Material::setShinnes(const qreal &shinnes){
    m_shinnes = shinnes;
}
const float &Material::shinnes() const{
    return m_shinnes;
}

void Material::setTransparency(const qreal &transparency){
    m_transparency = transparency;
}

const float &Material::transparency() const{
    return m_transparency;
}

void Material::setDiffuseMap(const QString &filepath){
    m_diffuseMap = QImage(filepath);
    m_isUsingDiffuseMap = true;
}

void Material::setDiffuseMap(const QImage &imageFile){
    m_diffuseMap = imageFile;
    m_isUsingDiffuseMap = true;
}

const QImage &Material::diffuseMap() const{
    return m_diffuseMap;
}

bool Material::isUsingDiffuseMap() const{
    return m_isUsingDiffuseMap;
}

void Material::setNormalMap(const QString &filepath){
    m_normalMap = QImage(filepath);
    m_isUsingNormalMap = true;
}

void Material::setNormalMap(const QImage &imageFile){
    m_normalMap = imageFile;
    m_isUsingNormalMap = true;
}

const QImage &Material::normalMap() const{
    return m_normalMap;
}

bool Material::isUsingNormalMap() const{
    return m_isUsingNormalMap;
}
