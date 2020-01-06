
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
    const double PI = 3.1415926535897932384626433832795;
    int frame = 0;
    float wind;
    float mass;
    float radius;
    float restitution;
    float red;
    float blue;
    float green;

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
    int startTime = GetTickCount();
    float xcoord;
    float ycoord;
    float xSpeed;
    float friction;
    float newTime;
    float oldTime = GetTickCount();
    float drag;
    float top;
    float v;

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
    void setColour(float r, float g, float b);
    void setFriction(float f);
    void simulatePhysics();
    void setDrag(float airRes);
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
     void gameLoop();
};
