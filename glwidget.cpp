#include <glwidget.h>

const double PI = 3.1415926535897932384626433832795;
double SKIP_TICKS;
int startTime;

int g_current_frame_number;

float nextGameTick;

glWidget::glWidget(QWidget * parent) : QOpenGLWidget(parent)
{

    rotationX = 0.0f;//set initial values
    rotationY = 0.0f;
    rotationZ = 0.0f;
    zoom = 1.0f;
    xPos = 0.0f;
    yPos = -0.5f;
    pause = false;
}

//void glWidget::animate(){//not working -> may have to revert to original timer() method
//    update();
//    SKIP_TICKS = 1000.0f / FPS;
//    int nextGameTick = GetTickCount();
//    nextGameTick += SKIP_TICKS;
//    int sleepTime = nextGameTick - GetTickCount();	//Time remaining until next frame
//    if (GetTickCount() - startTime >= 1000)				//If one second has passed update FPS
//    {
//        startTime = GetTickCount();
//    }

//    if (sleepTime > 0)
//    {
//        QThread::msleep(sleepTime);
//    }

//}

glWidget::~glWidget()
{
}

void glWidget::timer(float frames){//v v simple timer using Sleep
    float sleepTime;
    sleepTime = 1000 / frames;
    Sleep(sleepTime);

}
void glWidget::resizeGL(int width, int height)
{

    glViewport(0, 0, width, height);

    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();

    perspectiveGL(120.0f, (GLfloat)width/(GLfloat)height, 0.1f, 100.0f);
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();

}

void glWidget::initializeGL()
{
    //startTime = GetTickCount();
    //QTimer *aTimer = new QTimer;
    //connect(aTimer,SIGNAL(timeout()),this,SLOT(animate()));
    //aTimer->start(0);
    glClearColor(0.0, 0.0, 0.0, 0.0);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    glOrtho(0.0, 1.0, 0.0, 1.0, -1.0, 1.0);

}

float xSpeed=0.01f;
float minus = 0.0;
float vel = 0.0;
float frameAcc = 0.001;
float xc;
float yc;
float oldyc;
void glWidget::paintGL()
{

    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT); // Clear The Screen And The Depth Buffer
    glLoadIdentity();                   // Reset The View
    glTranslatef(xPos,yPos,-1.0f);             // Move Left And Into The Screen
    glScalef(zoom,zoom,1.0f);
    glClear(GL_COLOR_BUFFER_BIT);
    double PI=3.14159265;
    float top = posy+0.1f;
    float pos1 = posy;
    float pos2;
    float mass;


    if (pause == false){//when paused position doesn't change

    if (posx+radius>1.0f || posx-radius<=-1.0f)
    {
        xSpeed*=-1;
    }
    if (posy+radius>top || posy-radius<=-1.0f)//when at top or bottom of screen reverse bounce
    {
        ySpeed*=-1;
        if (posy-radius <=1.0f){
            ySpeed *= restitution;
            top -= 0.001;
        }
    }
    float v = sqrt(2 * 9.81f * posy)/100;
    //ySpeed = v * restitution;
    ySpeed -= 0.001f;

    posx+=wind;//add wind speed to position on x axis
    posy+=ySpeed;// add gravity to y position
    top -= 0.001f;// bring top value down to make ball bounce

    }

    glBegin(GL_POLYGON);
    for (float angle = 0;angle<360;angle++)//draw ball
    {
        //work out x and y coords at each point using pi and radius
        xc=sin(angle*PI/180) * radius;
        yc=cos(angle*PI/180) * radius;
        glColor3f(1.0f,0.0f,0.0f);          // red
        glVertex3f( xc+posx, yc+posy ,0.0f);// draw each points, using x,y coords and forces acting on the ball
    }

    glEnd();

    glBegin(GL_POLYGON);//draw the floor
    glColor3f(0.0f,0.0f,1.0f);
    glVertex3f( -10.0f, -5.0f, 0.0f);
    glVertex3f( -10.0f,  -1.0f, 0.0f);
    glVertex3f(  10.0f,  -1.0f, 0.0f);
    glVertex3f(  10.0f, -5.0f, 0.0f);
    glEnd();
    glFlush();
    timer(FPS);
    frame++;
    update();
    //}

}

void glWidget::pauseAnimation(){
    pause = true;
    update();
}
void glWidget::timerEvent(QTimerEvent *event)//not in use
{

    mRotateTriangle += 0.2f;
    mRotateQuad -= 0.15f;

    update();

    QOpenGLWidget::timerEvent(event);
}

void glWidget::keyPressEvent(QKeyEvent *event)
{
    switch (event->key()) {
    case Qt::Key_F2:
    {
        mFullScreen = !mFullScreen;
        if(mFullScreen) {
            showFullScreen();
        }
        else {
            showNormal();
        }
        update();
        break;
    }
    case Qt::Key_Escape:
    {
        qApp->exit();
        break;
    }
    case Qt::Key_Space://pause animation
    {
        pause = true;
        break;
    }
    case Qt::Key_Return://play/unpause animation
    {
        pause = false;
        break;
    }
    case Qt::Key_Left://move camera left
    {
        xPos += 0.1f;
        break;
    }
    case Qt::Key_Right://move camera right
    {
        xPos -= 0.1f;
        break;
    }
    case Qt::Key_Up://move camera up
    {
        yPos -= 0.1f;
        break;
    }
    case Qt::Key_Down://move camera down
    {
        yPos += 0.1f;
        break;
    }
    }
}

// Replaces gluPerspective
// fovY     - Field of vision in degrees in the y direction
// aspect   - Aspect ratio of the viewport
// zNear    - The near clipping distance
// zFar     - The far clipping distance

void glWidget::perspectiveGL( GLdouble fovY, GLdouble aspect, GLdouble zNear, GLdouble zFar )
{
    const GLdouble pi = 3.1415926535897932384626433832795;
    GLdouble fW, fH;
    fH = tan( (fovY / 2) / 180 * pi ) * zNear;
    fH = tan( fovY / 360 * pi ) * zNear;
    fW = fH * aspect;
    glFrustum( -fW, fW, -fH, fH, zNear, zFar );
}

//Use mouse movement to move camera
void glWidget::mouseMoveEvent(QMouseEvent *event)
{
    GLfloat dx = event->x() - lastPos.x();//change in x and y coords
    GLfloat dy = event->y() - lastPos.y();

    if (event->buttons() & Qt::LeftButton) {
        xPos -= dx/100;
        yPos -= dy/100;
        //update();
    }
    lastPos = event->pos();
}

void glWidget::mousePressEvent(QMouseEvent *event)
{

    lastPos = event->pos();
}


void glWidget::mouseDoubleClickEvent(QMouseEvent *event)//zoom in by double clicking
{
    if (zoom <= 3.0f){//zoom by double clicking
        zoom += 0.2f;

    }
}

void glWidget::wheelEvent(QWheelEvent *event){//can also zoom using mouse scroll or touchpad pinch
      QPoint numDegrees = event->angleDelta();//get the angle of the mouse scroll
      if (numDegrees.y() < 0)//zoom out
      {
          zoom = zoom/1.1;
      }
      if (numDegrees.y() > 0){//zoom in

          zoom = zoom*1.1;
      }
}

void glWidget::setWind(float w){
    wind = w;
}

void glWidget::setSpeed(float v){
    ySpeed = (v*9.81f)/1000;

}
void glWidget::setFPS(float framesSecond){
    FPS = framesSecond;
}
void glWidget::reset(){

}

void glWidget::setX(){

}

void glWidget::setStartPos(float x, float y){
    posx = x;
    posy = y;
}

void glWidget::setRadius(float rad){
    radius = rad;
}

void glWidget::setResitution(float colResistution){
    restitution = colResistution/10;
}
