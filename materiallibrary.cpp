#include "materiallibrary.h"
#include "material.h"

#include <QFile>
#include <QFileInfo>
#include <QTextStream>
#include <QDebug>

MaterialLibrary::MaterialLibrary(){}

void MaterialLibrary::addMaterial(Material *material){
    if(!material) return;

    for(int i = 0; i < m_materials.size(); ++i)
        if(m_materials[i] == material)
            return;

    m_materials.append(material);
}

Material *MaterialLibrary::getMaterial(quint32 index){
    if(index < (quint32)m_materials.size()){
        return m_materials[index];
    }else{
        return 0;
    }
}

Material *MaterialLibrary::getMaterial(const QString &mtlName){
    for(int i = 0; i < m_materials.size();++i)
        if(m_materials[i]->mtlName() == mtlName)
            return m_materials[i];

    return 0;
}

quint32 MaterialLibrary::getCounstMaterials(){
    return m_materials.size();
}

void MaterialLibrary::loadMaterialsFromFile(const QString &filename){
    QFile m_mtlFile(filename);

    if(!m_mtlFile.exists()){
        qDebug() << "File not fount" << filename;
        return;
    }
    m_mtlFile.open(QIODevice::ReadOnly);
    for(int i = 0;i < m_materials.size() ; ++i)
        delete m_materials[i];

    m_materials.clear();


    QFileInfo fileInfo(filename);
    QTextStream m_inputStream(&m_mtlFile);
    Material *newMtl = 0;

    while(!m_inputStream.atEnd()){
        QString line = m_inputStream.readLine();
        QStringList list = line.split(" ");

//        if (list[0] == "#") {
//            qDebug() << "This is comment" << line;
//            continue;
//        }
        if(list[0] == "newmtl"){
            newMtl = new Material;
            addMaterial(newMtl);
            newMtl->setName(list[1]);
            continue;
        }
        if(list[0] == "Ns"){
            newMtl->setShinnes(list[1].toFloat());
            continue;
        }
        if(list[0] == "Ka"){
            newMtl->setAmbientceColor(QVector3D(list[1].toFloat(), list[2].toFloat(), list[3].toFloat()));
            continue;
        }
        if(list[0] == "Kd"){
            newMtl->setDiffuseColor(QVector3D(list[1].toFloat(), list[2].toFloat(), list[3].toFloat()));
            continue;
        }
        if(list[0] == "Ks"){  // "сила блика"
            newMtl->setSpecularColor(QVector3D(list[1].toFloat(), list[2].toFloat(), list[3].toFloat()));
            continue;
        }
        if(list[0] == "Ni"){
            qDebug() << "Ni line transparency" << list[0];
            continue;
        }
        if (list[0] == "d"){
            qDebug() << "d line" << list[0];
            newMtl->setTransparency(list[1].toFloat());
            continue;
        }
        if (list[0] == "illum"){
            qDebug() << "illum line" << list[0];
            continue;
        }
        if(list[0] == "map_Kd"){
            qDebug() << fileInfo.absolutePath() << " " << list[1];
            newMtl->setDiffuseMap(QString("%1/%2").arg(fileInfo.absolutePath()).arg(list[1]));
            continue;
        }
        if(list[0] == "map_Bump"){
            qDebug() << fileInfo.absolutePath() << " " << list[1];
            newMtl->setNormalMap(QString("%1/%2").arg(fileInfo.absolutePath()).arg(list[1]));
            continue;
        }
    }

    addMaterial(newMtl);

    m_mtlFile.close();
}
