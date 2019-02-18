#ifndef MATERIALLIBRARY_H
#define MATERIALLIBRARY_H

#include <QVector>

class Material;

class MaterialLibrary{
public:
    MaterialLibrary();
    void addMaterial(Material *material);
    Material *getMaterial(quint32 index);
    Material *getMaterial(const QString &mtlName);
    quint32 getCounstMaterials();
    void loadMaterialsFromFile(const QString &filename);
private:
    QVector<Material *> m_materials;
};

#endif // MATERIALLIBRARY_H
