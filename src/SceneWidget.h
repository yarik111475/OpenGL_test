#ifndef SCENEWIDGET_H
#define SCENEWIDGET_H

#include <QTimer>
#include <QOpenGLWidget>
#include <QOpenGLFunctions>

class SceneWidget : public QOpenGLWidget,protected QOpenGLFunctions
{
    Q_OBJECT
private:
    GLfloat leftRed_ {1.0};
    GLfloat leftGreen_ {1.0};
    GLfloat leftBlue_ {1.0};

    GLfloat red_  {};
    GLfloat green_ {};
    GLfloat blue_  {};
    GLfloat xAxis_ {1.0f};
    GLfloat yAxis_ {0.0f};
    GLfloat zAxis_ {0.0f};
    GLfloat rotationAxis_ {};
    GLfloat rotationAngle_ {};
    QTimer timer_;
    GLuint pyramidDisplayNumber_ {};
    GLuint cylinderDisplayNumber_ {};

    GLuint createPyramid(GLfloat size=1.0);
    GLuint createCylinder(GLfloat radius,GLfloat height,const QColor& color);
protected:
    virtual void initializeGL()override;
    virtual void paintGL()override;
    virtual void resizeGL(int w, int h)override;
public:
    explicit SceneWidget(QWidget* parent=nullptr);
    virtual ~SceneWidget()=default;
public slots:
    void setLeftColorSlot(float red,float green,float blue);
    void setRotationEnabledSlot(bool enable);
    void setRotationAxisSlot(const QString& axis);
    void setFigureColorSlot(double red,double green, double blue);
private slots:
    void timeoutSlot();
};

#endif // SCENEWIDGET_H
