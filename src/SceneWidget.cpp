#include "SceneWidget.h"
#include <cmath>
#define PI 3.1415927


GLuint SceneWidget::createPyramid(GLfloat size)
{
    GLuint displayNumber {glGenLists(1)};
    glNewList(displayNumber,GL_COMPILE);
    {
        glBegin(GL_TRIANGLE_FAN);
        {
            glColor4f(0.0f, 1.0f, 0.0f, 1.0f);
            glVertex3f(0.0, size, 0.0);
            glVertex3f(-size, -size, size);
            glVertex3f(size, -size, size);
            glColor4f(rightRed_, rightGreen_, rightBlue_, 1.0f);
            glVertex3f(size, -size, -size);
            glColor4f(0.0f, 0.0f, 1.0f, 1.0f);
            glVertex3f(-size, -size, -size);
            glColor4f(leftRed_, leftGreen_, leftBlue_, 1.0f);
            glVertex3f(-size, -size, size);
        }
        glEnd();
        glBegin(GL_QUADS);
        {
            glColor4f(1.0f, 0.0f, 0.0f, 1.0f);
            glVertex3f(-size, -size, size);
            glVertex3f(size, -size, size);
            glVertex3f(size, -size, -size);
            glVertex3f(-size, -size, -size);
        }
        glEnd();
    }
    glEndList();
    return displayNumber;
}

GLuint SceneWidget::createCylinder(GLfloat radius, GLfloat height, const QColor &color)
{
    GLuint displayNumber {glGenLists(1)};
    glNewList(displayNumber,GL_COMPILE);
    {
        GLfloat x              = 0.0;
        GLfloat y              = 0.0;
        GLfloat angle          = 0.0;
        GLfloat angle_stepsize = 0.1;

        const auto r {color.redF()};
        const auto g {color.greenF()};
        const auto b {color.blueF()};
        glColor3f(r,g,b);
        glBegin(GL_QUAD_STRIP);
        {
            while( angle < 2*PI ) {
                x = radius * cos(angle);
                y = radius * sin(angle);
                glVertex3f(x, y , height);
                glVertex3f(x, y , 0.0);
                angle = angle + angle_stepsize;
            }
            glVertex3f(radius, 0.0, height);
            glVertex3f(radius, 0.0, 0.0);
        }
        glEnd();
        QColor newColor {color.lighter()};
        const auto lR {newColor.redF()};
        const auto lG {newColor.greenF()};
        const auto lB {newColor.blueF()};
        glColor3f(lR,lG,lB);
        glBegin(GL_POLYGON);
        {
            angle = 0.0;
            while( angle < 2*PI ) {
                x = radius * cos(angle);
                y = radius * sin(angle);
                glVertex3f(x, y , height);
                angle = angle + angle_stepsize;
            }
            glVertex3f(radius, 0.0, height);
        }
        glEnd();
    }
    glEndList();
    return displayNumber;
}

void SceneWidget::initializeGL()
{
    initializeOpenGLFunctions();
    glClearColor(0.0f,0.0f,0.0f,0.0f);
    glEnable(GL_DEPTH_TEST);
    glShadeModel(GL_FLAT);
    pyramidDisplayNumber_=createPyramid(1.0f);
    cylinderDisplayNumber_=createCylinder(1.0f,1.0f,QColor(red_,green_,blue_));
}

void SceneWidget::paintGL()
{
    glClear(GL_COLOR_BUFFER_BIT|GL_DEPTH_BUFFER_BIT);
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
    glTranslatef(0.0f,0.0f,-5.0f);
    //glRotatef(-25.0f,1.0f,0.0f,1.0f);
    glRotatef((GLfloat)rotationAngle_,xAxis_,yAxis_,zAxis_);
    //glCallList(cylinderDisplayNumber_);
    glCallList(pyramidDisplayNumber_);
}

void SceneWidget::resizeGL(int w, int h)
{
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    glViewport(0, 0, (GLint)w, (GLint)h);
    glFrustum(-1.0,1.0,-1.0,1.0,1.0,10.0);
}

SceneWidget::SceneWidget(QWidget *parent)
    :QOpenGLWidget{parent}
{
    timer_.setInterval(5);
    QObject::connect(&timer_,&QTimer::timeout,
                     this,&SceneWidget::timeoutSlot);
}

void SceneWidget::setLeftColorSlot(float red, float green, float blue)
{
    timer_.stop();
    leftRed_=red;
    leftGreen_=green;
    leftBlue_=blue;
    pyramidDisplayNumber_=createPyramid(1.0f);
    timer_.start();
}

void SceneWidget::setRightColorSlot(float red, float green, float blue)
{
    timer_.stop();
    rightRed_=red;
    rightGreen_=green;
    rightBlue_=blue;
    pyramidDisplayNumber_=createPyramid(1.0f);
    timer_.start();
}

void SceneWidget::setRotationEnabledSlot(bool enable)
{
    if(enable){
        rotationAngle_=0.0f;
        xAxis_=1.0f;
        yAxis_=0.0f;
        zAxis_=0.0f;
        timer_.start();
    }
    else{
        timer_.stop();
        rotationAngle_=0.0f;
        xAxis_=0.0f;
        yAxis_=0.0f;
        zAxis_=0.0f;
        update();
    }
}

void SceneWidget::setRotationAxisSlot(const QString &axis)
{
    timer_.stop();
    if(axis=="x"){
        xAxis_=1.0f;
        yAxis_=0.0f;
        zAxis_=0.0f;
    }
    else if(axis=="y"){
        xAxis_=0.0f;
        yAxis_=1.0f;
        zAxis_=0.0f;
    }
    else if(axis=="z"){
        xAxis_=0.0f;
        yAxis_=0.0f;
        zAxis_=1.0f;
    }
    timer_.start();
}

void SceneWidget::setFigureColorSlot(double red, double green, double blue)
{

}

void SceneWidget::timeoutSlot()
{
    rotationAngle_+=1.0;
    if(rotationAngle_>=360.0){
        rotationAngle_=0.0;
    }
    update();
}
