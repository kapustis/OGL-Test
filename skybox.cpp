#include "skybox.h"
#include "simpleobject3d.h"
#include "material.h"

SkyBox::SkyBox(float width , const QImage &texture){
    float width_div_2 = width / 2.0f;
    QVector<VertexData> vertexes;
    /* VertexData(QVector3D (x,y,z)) , текстурные коокдинаты(x,y),нормаль(x,y,z)*/

    //* первая грань - позади нас */
    vertexes.append(VertexData(QVector3D(-width_div_2,width_div_2,width_div_2) ,QVector2D(1.0,2.0/3.0)    ,QVector3D(0.0,0.0,-1.0)));
    vertexes.append(VertexData(QVector3D(-width_div_2,-width_div_2,width_div_2),QVector2D(1.0,1.0/3.0)    ,QVector3D(0.0,0.0,-1.0)));
    vertexes.append(VertexData(QVector3D(width_div_2,width_div_2,width_div_2)  ,QVector2D(3.0/4.0,2.0/3.0),QVector3D(0.0,0.0,-1.0)));
    vertexes.append(VertexData(QVector3D(width_div_2,-width_div_2,width_div_2) ,QVector2D(3.0/4.0,1.0/3.0),QVector3D(0.0,0.0,-1.0)));
    //* первая грань */

    //* вторая грань - справа от нас */
    vertexes.append(VertexData(QVector3D(width_div_2,width_div_2,width_div_2)  ,QVector2D(3.0/4.0,2.0/3.0),QVector3D(-1.0,0.0,0.0)));
    vertexes.append(VertexData(QVector3D(width_div_2,-width_div_2,width_div_2) ,QVector2D(3.0/4.0,1.0/3.0),QVector3D(-1.0,0.0,0.0)));
    vertexes.append(VertexData(QVector3D(width_div_2,width_div_2,-width_div_2) ,QVector2D(2.0/4.0,2.0/3.0),QVector3D(-1.0,0.0,0.0)));
    vertexes.append(VertexData(QVector3D(width_div_2,-width_div_2,-width_div_2),QVector2D(2.0/4.0,1.0/3.0),QVector3D(-1.0,0.0,0.0)));
    //* вторая грань */

    //* третья грань -над нами */
    vertexes.append(VertexData(QVector3D(width_div_2,width_div_2,width_div_2)  ,QVector2D(2.0/4.0,1.0)    ,QVector3D(0.0,-1.0,0.0)));
    vertexes.append(VertexData(QVector3D(width_div_2,width_div_2,-width_div_2) ,QVector2D(2.0/4.0,2.0/3.0),QVector3D(0.0,-1.0,0.0)));
    vertexes.append(VertexData(QVector3D(-width_div_2,width_div_2,width_div_2) ,QVector2D(1.0/4.0,1.0)    ,QVector3D(0.0,-1.0,0.0)));
    vertexes.append(VertexData(QVector3D(-width_div_2,width_div_2,-width_div_2),QVector2D(1.0/4.0,2.0/3.0),QVector3D(0.0,-1.0,0.0)));
    //* третья грань */

    //* четвертая грань - перед нами */
    vertexes.append(VertexData(QVector3D(width_div_2,width_div_2,-width_div_2)  ,QVector2D(2.0/4.0,2.0/3.0),QVector3D(0.0,0.0,1.0)));
    vertexes.append(VertexData(QVector3D(width_div_2,-width_div_2,-width_div_2) ,QVector2D(2.0/4.0,1.0/3.0),QVector3D(0.0,0.0,1.0)));
    vertexes.append(VertexData(QVector3D(-width_div_2,width_div_2,-width_div_2) ,QVector2D(1.0/4.0,2.0/3.0),QVector3D(0.0,0.0,1.0)));
    vertexes.append(VertexData(QVector3D(-width_div_2,-width_div_2,-width_div_2),QVector2D(1.0/4.0,1.0/3.0),QVector3D(0.0,0.0,1.0)));
    //* четвертая грвнь */

    //* - слева от нас */
    vertexes.append(VertexData(QVector3D(-width_div_2,width_div_2,width_div_2)  ,QVector2D(0.0,2.0/3.0)    ,QVector3D(1.0,0.0,0.0)));
    vertexes.append(VertexData(QVector3D(-width_div_2,width_div_2,-width_div_2) ,QVector2D(1.0/4.0,2.0/3.0),QVector3D(1.0,0.0,0.0)));
    vertexes.append(VertexData(QVector3D(-width_div_2,-width_div_2,width_div_2) ,QVector2D(0.0,1.0/3.0)    ,QVector3D(1.0,0.0,0.0)));
    vertexes.append(VertexData(QVector3D(-width_div_2,-width_div_2,-width_div_2),QVector2D(1.0/4.0,1.0/3.0),QVector3D(1.0,0.0,0.0)));

    //* шестая грань - под нами */
    vertexes.append(VertexData(QVector3D(-width_div_2,-width_div_2,width_div_2) ,QVector2D(1.0/4.0,0.0)    ,QVector3D(0.0,1.0,0.0)));
    vertexes.append(VertexData(QVector3D(-width_div_2,-width_div_2,-width_div_2),QVector2D(1.0/4.0,1.0/3.0),QVector3D(0.0,1.0,0.0)));
    vertexes.append(VertexData(QVector3D(width_div_2,-width_div_2,width_div_2)  ,QVector2D(2.0/4.0,0.0)    ,QVector3D(0.0,1.0,0.0)));
    vertexes.append(VertexData(QVector3D(width_div_2,-width_div_2,-width_div_2) ,QVector2D(2.0/4.0,1.0/3.0),QVector3D(0.0,1.0,0.0)));
    //* шестая грань */

    QVector<GLuint> indexes;

    for(int i = 0; i < 24; i+=4){
        indexes.append(i+0);
        indexes.append(i+2);
        indexes.append(i+1);

        indexes.append(i+2);
        indexes.append(i+3);
        indexes.append(i+1);
    }

    Material *newMtl = new Material;
    newMtl->setDiffuseMap(texture);
    newMtl->setShinnes(96);
    newMtl->setDiffuseColor(QVector3D(1.0,1.0,1.0));
    newMtl->setAmbientceColor(QVector3D(1.0,1.0,1.0));
    newMtl->setSpecularColor(QVector3D(1.0,1.0,1.0));

    m_cube = new SimpleObject3D(vertexes,indexes,newMtl);
}

SkyBox::~SkyBox(){
    delete m_cube;
}
void SkyBox::draw(QOpenGLShaderProgram *program, QOpenGLFunctions *function){
//    m_cube->translate(QVector3D(0.0f,200.0f,0.0f));
    m_cube->draw(program,function);
}

void SkyBox::rotate(const QQuaternion &r){
    (void)r;
}

void SkyBox::translate(const QVector3D &t){
    (void)t;
}

void SkyBox::scale(const float &s){
    (void)s;
}

void SkyBox::setGlobalTransform(const QMatrix4x4 &g){
    (void)&g;
}

