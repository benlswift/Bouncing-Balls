
#include <QGLWidget>
#include <QKeyEvent>
#include <QMouseEvent>
#include <QOpenGLWidget>
#include <math.h>
#include <time.h>
#include <stdio.h>
#include <stdlib.h>
#include <iostream>
#include <QTimer>
#include "mainwindow.h"
#include <QApplication>
#include <QtOpenGL>
#include <GL/glu.h>

class glWidget : public QOpenGLWidget
{
    Q_OBJECT

public:
    explicit glWidget(QWidget *parent = 0);

    ~glWidget();
    float ang,x,y;
    float ty=-0.8,sx=0.1,sy=0.1;
    int flag=0,cnt=0;
    const double PI = 3.1415926535897932384626433832795;
    //Camera variables
    GLdouble fov = 40.0, nearZ = 1, farZ = 20, theta = 0, phi = 135;
    GLdouble eyePos[3] = { radius*cosf(phi*PI / 180.0f)*sinf(theta*PI / 180.0f) ,radius*sinf(phi*PI / 180.0f) ,radius*cosf(phi*PI / 180.0f)*cosf(theta*PI / 180.0f) };	//Using spherical coords
    GLdouble targetPos[3] = { 0, 0, 2 };
    GLdouble up[3] = { 0,1,0 };
    int frame = 0;
    float wind;
    float mass;
    float radius;
    float restitution;

    //Last point of mouse click used in camera
    QPoint lastPos;
    GLfloat rotationX;
    GLfloat rotationY;
    GLfloat rotationZ;
    GLfloat xPos;
    GLfloat yPos;
    GLfloat zoom;
    float posx;
    float posy;
    float ySpeed;
    bool pause;
    float FPS = 60.0f;

    void perspectiveGL(GLdouble fovY, GLdouble aspect, GLdouble zNear, GLdouble zFar);
    void CreateSphere(double R);
    void recalculateEyePos();
    void mouseMoveEvent(QMouseEvent *event);
    void mousePressEvent(QMouseEvent *event);
    void glLookAt(GLfloat x, GLfloat y, GLfloat z, GLfloat rx, GLfloat ry, GLfloat rz);
    void mouseDoubleClickEvent(QMouseEvent *event);
    void pauseAnimation();
    void setWind(float w);
    void setSpeed(float v);
    void reset();
    void setX();
    void setStartPos(float, float);
    void setRadius(float );
    void timer(float);
    void setFPS(float);
    void setResitution(float colResistution);
    void wheelEvent(QWheelEvent *event);
protected:

    virtual void paintGL();
    virtual void initializeGL();
    virtual void resizeGL(int width, int height);
    virtual void timerEvent(QTimerEvent *event);
    virtual void keyPressEvent(QKeyEvent *event);

private:

    bool mFullScreen;
    QBasicTimer time;
    GLfloat mRotateTriangle;
    GLfloat mRotateQuad;

private slots:
     //void animate();
};
