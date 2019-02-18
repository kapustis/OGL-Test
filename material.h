#ifndef MATERIAL_H
#define MATERIAL_H

#include <QString>
#include <QVector3D>
#include <QImage>

class Material{
public:
    Material();
    void setName(const QString &mtlName);
    const QString &mtlName() const;
    void setDiffuseColor(const QVector3D &diffuseColor);
    const  QVector3D &diffuseColor() const;
    void setAmbientceColor(const QVector3D &ambientceColor);
    const  QVector3D &ambientceColor() const;
    void setSpecularColor(const QVector3D &specularColor);
    const  QVector3D &specularColor() const;
    void setShinnes (const qreal &shinnes);
    const float &shinnes() const;

    void setTransparency(const qreal &transparency);
    const float &transparency() const;

    void setDiffuseMap (const QString &filepath);
    void setDiffuseMap (const QImage &imageFile);
    const  QImage &diffuseMap() const;
    bool isUsingDiffuseMap() const;

    void setNormalMap (const QString &filepath);
    void setNormalMap (const QImage &imageFile);
    const  QImage &normalMap() const;
    bool isUsingNormalMap() const;

private:
    QString m_mtlName;          //имя материала
    QVector3D m_diffuseColor;
    QVector3D m_ambientceColor;
    QVector3D m_specularColor;
    float m_shinnes;
    float m_transparency;
    QImage m_diffuseMap;        //map_Kd
    QImage m_normalMap;        //map_Bump
    bool m_isUsingDiffuseMap;
    bool m_isUsingNormalMap;
};

#endif // MATERIAL_H
