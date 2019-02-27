#include "widget.h"
#include <objectengine3d.h>
#include <QMouseEvent>
#include <QKeyEvent>
#include <QOpenGLContext>
#include <QtMath>
#include <QOpenGLFramebufferObject>
#include <QOpenGLFunctions>
#include "group3d.h"
#include "camera3d.h"
#include "skybox.h"
#include "material.h"
#include "light.h"


Widget::Widget(QWidget *parent): QOpenGLWidget(parent){
    m_camera = new Camera3D;
    m_camera->translate(QVector3D(0.0,0.0,-15.0));
    m_fbHeight = (quint32)sizeShadow;
    m_fbWidth  = (quint32)sizeShadow;
    m_projectionLightMatrix.setToIdentity();
    m_projectionLightMatrix.ortho(-40.0, 40.0, -40.0, 40.0, -40.0, 40.0);

    angleObject = 0.0f;
    angleGroup1 = 0.0f;
    angleGroup2 = 0.0f;
    angleMain   = 0.0f;

    m_light0[0] = new Light(Light::Spot);
    m_light0[0]->setPosition(QVector4D(10.0f,10.0f,10.0f,1.0f));
    m_light0[0]->setDirection(QVector4D(-1.0f,-1.0f,-1.0f,0.0f));
    m_light0[0]->setDiffuseColor(QVector3D(1.0f,0.0f,0.0f));
    m_light0[0]->setCutoff(10.0 / 180.0 * M_PI);

    m_light0[1] = new Light(Light::Spot);
    m_light0[1]->setPosition(QVector4D(-10.0f,10.0f,10.0f,1.0f));
    m_light0[1]->setDirection(QVector4D(1.0f,-1.0f,-1.0f,0.0f));
    m_light0[1]->setDiffuseColor(QVector3D(0.0f,1.0f,0.0f));
    m_light0[1]->setCutoff(12.0 / 180.0 * M_PI);

    m_light0[2] = new Light(Light::Spot);
    m_light0[2]->setPosition(QVector4D(10.0f,10.0f,-10.0f,1.0f));
    m_light0[2]->setDirection(QVector4D(-1.0f,-1.0f,1.0f,0.0f));
    m_light0[2]->setDiffuseColor(QVector3D(0.0f,0.0f,1.0f));
    m_light0[2]->setCutoff(15.0 / 180.0 * M_PI);
}

Widget::~Widget(){
    delete m_camera;
    for(int i;i < m_objects.size();++i) delete m_objects[i];
    for(int i;i < m_groups.size();++i) delete m_groups[i];
}

void Widget::initializeGL(){   
    glClearColor(0.0,0.0,0.0,1.0);
    //    glMatrixMode(GL_PROJECTION);
    glEnable(GL_DEPTH_TEST);
    glEnable(GL_CULL_FACE);
    //    glEnable(GL_ALPHA_TEST);

    initShaders();

    //    float step = 2.0f;
    QImage  DM(":/brick.jpg");
    QImage  NM(":/354-normal.jpg");
    float x = 0.0 , y = -1.0 ,z = 0.0;
    m_groups.append(new Group3D);
    //    for(float x = -step; x<= step; x += step){
    //        for(float y = -step; y <= step; y += step){
    //            for(float z = -step; z<= step; z +=step){
    //                initCube(1.0f,1.0f,1.0f,&DM,&NM);
    m_objects.append(new ObjectEngine3D);
    m_objects[m_objects.size() - 1]->loadObjectFromFile(":/model/cat/cat.obj");
    m_objects[m_objects.size() - 1]->translate(QVector3D(x,y,z));
    m_groups[m_groups.size() - 1]->addObject(m_objects[m_objects.size() - 1]);
    //            }
    //        }
    //    }
    m_groups[0]->translate(QVector3D(-4.0f,0.0f,0.0f));

    m_groups.append(new Group3D);
    //    for(float x = -step; x<= step; x += step){
    //        for(float y = -step; y <= step; y += step){
    //            for(float z = -step; z<= step; z +=step){
    //               initCube(1.0f,1.0f,1.0f,&DM,&NM);
    m_objects.append(new ObjectEngine3D);
    m_objects[m_objects.size() - 1]->loadObjectFromFile(":/model/cube/untitled.obj");
    m_objects[m_objects.size() - 1]->translate(QVector3D(x,y,z));
    m_groups[m_groups.size() - 1]->addObject(m_objects[m_objects.size() - 1]);
    //            }
    //        }
    //    }

    m_groups[1]->translate(QVector3D(4.0f,0.0f,0.0f));

    m_groups.append(new Group3D);
    m_groups[2]->addObject(m_groups[0]);
    m_groups[2]->addObject(m_groups[1]);

    m_TransformObjects.append(m_groups[2]);

    //    m_objects.append(new ObjectEngine3D);
    //    m_objects[m_objects.size() - 1]->loadObjectFromFile(":/model/1984_Kenworth_K_100_Mark_Truck/untitled.obj");
    //m_objects[m_objects.size() - 1]->loadObjectFromFile(":/model/my_cub/initCube.obj");

    initCube(2.0f,2.0f,2.0f,&DM,&NM);
    m_TransformObjects.append(m_objects[m_objects.size() - 1]);
    /* "поверхность" */
    QImage tDM(":/cube.jpg");
    initCube(40.0f,2.0f,40.0f,&tDM);
    m_objects[m_objects.size() - 1]->translate(QVector3D(0.0,-2.0,0.0));
    m_TransformObjects.append(m_objects[m_objects.size() - 1]);
    /* "поверхность" */
    m_groups[0]->addObject(m_camera);
    m_skybox = new SkyBox(100,QImage(":/skyboxtexture/skybox_texture.png"));

    m_depthBuffer = new QOpenGLFramebufferObject(m_fbWidth,m_fbHeight,QOpenGLFramebufferObject::Depth);

}

void Widget::resizeGL(int w, int h){
    float aspect = w / (h ? (float)h : 1);

    m_projectionMatrix.setToIdentity();
    m_projectionMatrix.perspective(45,aspect,0.01f,10000.1f);
}

void Widget::paintGL(){
    /** отрисовка во фреймбуффер*/

    m_depthBuffer->bind();
    glViewport(0,0,m_fbWidth,m_fbHeight);
    glClear(GL_COLOR_BUFFER_BIT| GL_DEPTH_BUFFER_BIT);

    m_programDepth.bind();
    m_programDepth.setUniformValue("u_projectionLightMatrix",m_projectionLightMatrix);
    m_programDepth.setUniformValue("u_shadowLightMatrix",m_light0[0]->getLightMatrix());

    for(int i = 0;i < m_TransformObjects.size();++i){
        m_TransformObjects[i]->draw(&m_programDepth,context()->functions());
    }
    m_programDepth.release();

    m_depthBuffer->release();

    GLuint texture = m_depthBuffer->texture();

    context()->functions()->glActiveTexture(GL_TEXTURE4);
    glBindTexture(GL_TEXTURE_2D, texture);

    /** отрисовка на экран*/
    glViewport(0,0,width(),height());
    glClear(GL_COLOR_BUFFER_BIT| GL_DEPTH_BUFFER_BIT);
    /*-skybox*/
    m_programSkyBox.bind();
    m_programSkyBox.setUniformValue("u_projectionMatrix",m_projectionMatrix);

    m_camera->draw(&m_programSkyBox);
    m_skybox->draw(&m_programSkyBox,context()->functions());
    m_programSkyBox.release();
    /*-skybox*/
    m_program.bind();
    m_program.setUniformValue("u_shadowMap",GL_TEXTURE4 - GL_TEXTURE0);
    m_program.setUniformValue("u_sizeShadow",sizeShadow);
    m_program.setUniformValue("u_projectionMatrix",m_projectionMatrix);
    m_program.setUniformValue("u_projectionLightMatrix",m_projectionLightMatrix);
    m_program.setUniformValue("u_shadowLightMatrix",m_light0[0]->getLightMatrix());
    m_program.setUniformValue("u_lightPower", 2.0f);
    for(int i = 0; i < 3; ++i){
        m_program.setUniformValue(QString("u_lightProperty[%1].ambienceColor").arg(i).toLatin1().data(),  m_light0[i]->getAmbienseColor());
        m_program.setUniformValue(QString("u_lightProperty[%1].diffuseColor").arg(i).toLatin1().data(),   m_light0[i]->getDiffuseColor());
        m_program.setUniformValue(QString("u_lightProperty[%1].specularColor").arg(i).toLatin1().data(),  m_light0[i]->getSpecularColor());
        m_program.setUniformValue(QString("u_lightProperty[%1].position").arg(i).toLatin1().data(),       m_light0[i]->getPosition());
        m_program.setUniformValue(QString("u_lightProperty[%1].direction").arg(i).toLatin1().data(),      m_light0[i]->getDirection());
        m_program.setUniformValue(QString("u_lightProperty[%1].cutoff").arg(i).toLatin1().data(),         m_light0[i]->getCutoff());
        m_program.setUniformValue(QString("u_lightProperty[%1].type").arg(i).toLatin1().data(),           m_light0[i]->getType());
    }
    m_program.setUniformValue("u_countLights",3);
    m_program.setUniformValue("u_indexLightForShadow",0);

    m_camera->draw(&m_program);

    for(int i = 0;i < m_TransformObjects.size();++i){
        m_TransformObjects[i]->draw(&m_program,context()->functions());
    }
    m_program.release();
}

void Widget::mousePressEvent(QMouseEvent *event){
    if(event->buttons() == Qt::LeftButton){
        m_mousePosition = QVector2D(event->localPos());
    }
    event->accept();
}

void Widget::mouseMoveEvent(QMouseEvent *event){
    if(event->buttons() != Qt::LeftButton) return;

    QVector2D diff = QVector2D(event->localPos()) - m_mousePosition;
    m_mousePosition = QVector2D(event->localPos());

    float angleX = diff.y() /2.0f;
    float angleY = diff.x() /2.0f;
    m_camera->rotateX(QQuaternion::fromAxisAndAngle(1.0f,0.0f,0.0f,angleX));
    m_camera->rotateY(QQuaternion::fromAxisAndAngle(0.0f,1.0f,0.0f,angleY));

    update();
}
/* переключение камеры между групами и обьектами */
void Widget::keyPressEvent(QKeyEvent *event){
    if(event->key() == Qt::Key_R || event->key() == 1050){
        if(m_timer.isActive()){
            m_timer.stop();
        }else{
            m_timer.start(30,this);
        }
    }

    switch (event->key()) {
    case Qt::Key_Right:
        m_groups[0]->delObject(m_camera);
        m_groups[1]->addObject(m_camera);
        break;
    case Qt::Key_Left :
        m_groups[1]->delObject(m_camera);
        m_groups[0]->addObject(m_camera);
        break;
    case Qt::Key_Down:
        m_groups[0]->delObject(m_camera);
        m_groups[1]->delObject(m_camera);
        break;
    case Qt::Key_Up:
        m_groups[0]->delObject(m_camera);
        m_groups[1]->delObject(m_camera);
        QMatrix4x4 tmp;
        tmp.setToIdentity();
        m_camera->setGlobalTransform(tmp);
        break;
    }
    update();
}
/* переключение камеры между групами и обьектами */

/* действие на движение колесо мыши "приближение-отдаление"*/
void Widget::wheelEvent(QWheelEvent *event){
    if(event->delta() > 0){
        m_camera->translate(QVector3D(0.0,0.0,0.25));
    }else if(event->delta() < 0){
        m_camera->translate(QVector3D(0.0,0.0,-0.25));
    }
    update();
}
/* действие на движение колесо мыши "приближение-отдаление"*/

void Widget::timerEvent(QTimerEvent *event){
    Q_UNUSED(event);
    for(int i = 0;i < m_objects.size() -2; ++i){
        if(i % 2 == 0){
            m_objects[i]->rotate(QQuaternion::fromAxisAndAngle(1.0f,0.0f,0.0f,qSin(angleObject)));
            m_objects[i]->rotate(QQuaternion::fromAxisAndAngle(0.0f,1.0f,0.0f,qCos(angleObject)));
        }else{
            m_objects[i]->rotate(QQuaternion::fromAxisAndAngle(0.0f,1.0f,0.0f,qSin(angleObject)));
            m_objects[i]->rotate(QQuaternion::fromAxisAndAngle(1.0f,0.0f,0.0f,qCos(angleObject)));
        }
    }

    m_groups[0]->rotate(QQuaternion::fromAxisAndAngle(0.0f,0.0f,1.0f,qSin(angleGroup1)));
    m_groups[0]->rotate(QQuaternion::fromAxisAndAngle(0.0f,1.0f,0.0f,-qSin(angleGroup1)));

    m_groups[1]->rotate(QQuaternion::fromAxisAndAngle(1.0f,0.0f,0.0f,qCos(angleGroup2)));
    m_groups[1]->rotate(QQuaternion::fromAxisAndAngle(0.0f,1.0f,0.0f,-qCos(angleGroup2)));


    m_groups[2]->rotate(QQuaternion::fromAxisAndAngle(1.0f,0.0f,0.0f,qSin(angleMain)));
    m_groups[2]->rotate(QQuaternion::fromAxisAndAngle(0.0f,1.0f,0.0f,qCos(angleMain)));

    angleObject += M_PI /180.0f;
    angleGroup1 += M_PI /360.0f;
    angleGroup2 -= M_PI /360.0f;
    angleMain   += M_PI /720.0f;

    update();
}

void Widget::initShaders(){
    if(!m_program.addShaderFromSourceFile(QOpenGLShader::Vertex, ":/vshader.vsh"))close();
    if(!m_program.addShaderFromSourceFile(QOpenGLShader::Fragment, ":/fshader.fsh"))close();
    if(!m_program.link())close();

    if(!m_programSkyBox.addShaderFromSourceFile(QOpenGLShader::Vertex, ":/skybox.vsh"))close();
    if(!m_programSkyBox.addShaderFromSourceFile(QOpenGLShader::Fragment, ":/skybox.fsh"))close();
    if(!m_programSkyBox.link())close();

    if(!m_programDepth.addShaderFromSourceFile(QOpenGLShader::Vertex, ":/depth.vsh"))close();
    if(!m_programDepth.addShaderFromSourceFile(QOpenGLShader::Fragment, ":/depth.fsh"))close();
    if(!m_programDepth.link())close();

}

void Widget::initCube(float width, float heigth, float depth,QImage *pathDiffuseMap,QImage *pathNormalMap){
    float width_div_2  = width  / 2.0f;
    float heigth_div_2 = heigth / 2.0f;
    float depth_div_2  = depth  / 2.0f;

    QVector<VertexData> vertexes;
    //* первая грань */
    vertexes.append(VertexData(QVector3D(-width_div_2,heigth_div_2,depth_div_2) ,QVector2D(0.0,1.0),QVector3D(0.0,0.0,1.0)));
    vertexes.append(VertexData(QVector3D(-width_div_2,-heigth_div_2,depth_div_2),QVector2D(0.0,0.0),QVector3D(0.0,0.0,1.0)));
    vertexes.append(VertexData(QVector3D(width_div_2,heigth_div_2,depth_div_2)  ,QVector2D(1.0,1.0),QVector3D(0.0,0.0,1.0)));
    vertexes.append(VertexData(QVector3D(width_div_2,-heigth_div_2,depth_div_2) ,QVector2D(1.0,0.0),QVector3D(0.0,0.0,1.0)));
    //* первая грань */

    //* вторая грань */
    vertexes.append(VertexData(QVector3D(width_div_2,heigth_div_2,depth_div_2)  ,QVector2D(0.0,1.0),QVector3D(1.0,0.0,0.0)));
    vertexes.append(VertexData(QVector3D(width_div_2,-heigth_div_2,depth_div_2) ,QVector2D(0.0,0.0),QVector3D(1.0,0.0,0.0)));
    vertexes.append(VertexData(QVector3D(width_div_2,heigth_div_2,-depth_div_2) ,QVector2D(1.0,1.0),QVector3D(1.0,0.0,0.0)));
    vertexes.append(VertexData(QVector3D(width_div_2,-heigth_div_2,-depth_div_2),QVector2D(1.0,0.0),QVector3D(1.0,0.0,0.0)));
    //* вторая грань */

    //* третья грань */
    vertexes.append(VertexData(QVector3D(width_div_2,heigth_div_2,depth_div_2)  ,QVector2D(0.0,1.0),QVector3D(0.0,1.0,0.0)));
    vertexes.append(VertexData(QVector3D(width_div_2,heigth_div_2,-depth_div_2) ,QVector2D(0.0,0.0),QVector3D(0.0,1.0,0.0)));
    vertexes.append(VertexData(QVector3D(-width_div_2,heigth_div_2,depth_div_2) ,QVector2D(1.0,1.0),QVector3D(0.0,1.0,0.0)));
    vertexes.append(VertexData(QVector3D(-width_div_2,heigth_div_2,-depth_div_2),QVector2D(1.0,0.0),QVector3D(0.0,1.0,0.0)));
    //* третья грань */

    //* четвертая грань */
    vertexes.append(VertexData(QVector3D(width_div_2,heigth_div_2,-depth_div_2)  ,QVector2D(0.0,1.0),QVector3D(0.0,0.0,-1.0)));
    vertexes.append(VertexData(QVector3D(width_div_2,-heigth_div_2,-depth_div_2) ,QVector2D(0.0,0.0),QVector3D(0.0,0.0,-1.0)));
    vertexes.append(VertexData(QVector3D(-width_div_2,heigth_div_2,-depth_div_2) ,QVector2D(1.0,1.0),QVector3D(0.0,0.0,-1.0)));
    vertexes.append(VertexData(QVector3D(-width_div_2,-heigth_div_2,-depth_div_2),QVector2D(1.0,0.0),QVector3D(0.0,0.0,-1.0)));
    //* четвертая грaнь */

    //* пятая грань */
    vertexes.append(VertexData(QVector3D(-width_div_2,heigth_div_2,depth_div_2)  ,QVector2D(0.0,1.0),QVector3D(-1.0,0.0,0.0)));
    vertexes.append(VertexData(QVector3D(-width_div_2,heigth_div_2,-depth_div_2) ,QVector2D(0.0,0.0),QVector3D(-1.0,0.0,0.0)));
    vertexes.append(VertexData(QVector3D(-width_div_2,-heigth_div_2,depth_div_2) ,QVector2D(1.0,1.0),QVector3D(-1.0,0.0,0.0)));
    vertexes.append(VertexData(QVector3D(-width_div_2,-heigth_div_2,-depth_div_2),QVector2D(1.0,0.0),QVector3D(-1.0,0.0,0.0)));
    //* пятая грань */

    //* шестая грань */
    vertexes.append(VertexData(QVector3D(-width_div_2,-heigth_div_2, depth_div_2),QVector2D(0.0,1.0),QVector3D(0.0,-1.0,0.0)));
    vertexes.append(VertexData(QVector3D(-width_div_2,-heigth_div_2,-depth_div_2),QVector2D(0.0,0.0),QVector3D(0.0,-1.0,0.0)));
    vertexes.append(VertexData(QVector3D(width_div_2,-heigth_div_2,  depth_div_2),QVector2D(1.0,1.0),QVector3D(0.0,-1.0,0.0)));
    vertexes.append(VertexData(QVector3D(width_div_2,-heigth_div_2, -depth_div_2),QVector2D(1.0,0.0),QVector3D(0.0,-1.0,0.0)));
    //* шестая грань */

    QVector<GLuint> indexes;

    for(int i=0; i < 24; i+=4){
        indexes.append(i+0);
        indexes.append(i+1);
        indexes.append(i+2);

        indexes.append(i+2);
        indexes.append(i+1);
        indexes.append(i+3);
    }

    Material *newMtl = new Material;
    if(pathDiffuseMap) newMtl->setDiffuseMap(*pathDiffuseMap);
    if(pathNormalMap) newMtl->setNormalMap(*pathNormalMap);
    newMtl->setShinnes(96);
    newMtl->setDiffuseColor(QVector3D(1.0,1.0,1.0));
    newMtl->setAmbientceColor(QVector3D(1.0,1.0,1.0));
    newMtl->setSpecularColor(QVector3D(1.0,1.0,1.0));

    ObjectEngine3D *newObj = new ObjectEngine3D;
    newObj->calculateTBN(vertexes);
    newObj->addObject(new SimpleObject3D(vertexes,indexes, newMtl));

    m_objects.append(newObj); // QImage(":/brick.jpg"))); //":/cube.jpg"
}

