#include <glwidget.h>

const double PI = 3.1415926535897932384626433832795;
double SKIP_TICKS;

int g_current_frame_number;

float nextGameTick;

glWidget::glWidget(QWidget * parent) : QOpenGLWidget(parent)
{

    rotationX = 0.0f;//set initial values
    rotationY = 0.0f;
    rotationZ = 0.0f;
    zoom = 1.2f;
    xPos = 0.0f;
    yPos = 0.2f;
    pause = false;
}

void glWidget::gameLoop(){
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
//        QThread::msleep(SKIP_TICKS);
//    }

}

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
    QTimer *timer = new QTimer;
    connect(timer,SIGNAL(timeout()),this,SLOT(gameLoop()));
    timer->start(0);

    glClearColor(0.0, 0.0, 0.0, 0.0);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    glOrtho(0.0, 10.0, 0.0, 10.0, -1.0, 1.0);

}

void glWidget::simulatePhysics(){
    //newTime = GetTickCount();
    float changeTime = 0.01;//timestep for calculating new position

    if (posy-radius<=-1.0f)//when at top or bottom of screen reverse bounce
    {
        if (posx+radius>1.5f || posx-radius<=-1.5f)//falls off table
        {
        }
        else{
        ySpeed*=-1;
        if (posy-radius <=1.0f){
            ySpeed *= restitution;
            ySpeed *= friction;//reduce speed due to friction of table/floor
            posy = -1.0 + radius;//reposition ball -- so doesn't fall through floor
        }
        }
    }
    ySpeed -= 9.81f * changeTime;
    ySpeed *= drag;//reduce speed due to air resistance/drag
    posy += (ySpeed * changeTime);
    std::cout << "Time change: " << changeTime << " newTime: " << newTime << " oldTime: " << oldTime <<std::endl;
    //posy = posy + ySpeed * changeTime + (0.5 * -0.0981 * pow(changeTime,2));
    wind *=drag;
    posx+=wind;//add wind speed to position on x axis
    //oldTime = GetTickCount();

    }
void glWidget::paintGL()
{
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT); // Clear The Screen And The Depth Buffer
    glLoadIdentity();                   // Reset The View
    glTranslatef(xPos,yPos,-1.0f);             // Move Left And Into The Screen
    glScalef(zoom,zoom,1.0f);
    glClear(GL_COLOR_BUFFER_BIT);


    if (pause == false){//when paused position doesn't change
    simulatePhysics();//do physics sim
    }
    glBegin(GL_POLYGON);
    for (float angle = 0;angle<360;angle++)//draw ball
    {
        //work out x and y coords at each point using pi and radius
        xcoord=sin(angle*PI/180) * radius;
        ycoord=cos(angle*PI/180) * radius;
        glColor3f(red,green,blue);
        glVertex3f( xcoord+posx, ycoord+posy ,0.0f);// draw each points, using x,y coords and forces acting on the ball
    }
    glEnd();

    glBegin(GL_POLYGON);//draw the table
    glColor3f(0.5f,0.2f,0.2f);
    glVertex3f( -1.4f, -1.20f, 0.0f);
    glVertex3f( -1.4f,  -1.0f, 0.0f);
    glVertex3f(  1.4f,  -1.0f, 0.0f);
    glVertex3f(  1.4f, -1.20f, 0.0f);
    glEnd();


    glBegin(GL_POLYGON);
    glColor3f(0.5f,0.2f,0.2f);
    glVertex3f( -1.4f, -1.20f, 0.0f);//left leg
    glVertex3f(  -1.4f,  -2.0f, 0.0f);// leg
    glVertex3f(  -1.2f, -2.0f, 0.0f);// leg
    glVertex3f( -1.2f,  -1.20f, 0.0f);//left leg

    glEnd();

    glBegin(GL_POLYGON);
    glColor3f(0.5f,0.2f,0.2f);
    glVertex3f( 1.4f, -1.20f, 0.0f);//right leg
    glVertex3f(  1.4f,  -2.0f, 0.0f);//right leg
    glVertex3f(  1.2f, -2.0f, 0.0f);//right leg
    glVertex3f( 1.2f,  -1.20f, 0.0f);//right leg

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
    ySpeed = (v*9.81f)/1000;//initial speed = mass * gravity
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
    restitution = colResistution;
}

void glWidget::setColour(float r, float g, float b){
    red = r/10;
    blue = b/10;
    green = g/10;
}

void glWidget::setFriction(float f){
    friction = 1-f/10;
}

void glWidget::setDrag(float airRes){
    airRes = airRes/100;
    drag = 1-airRes;
}
