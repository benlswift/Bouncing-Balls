#include "mainwindow.h"
#include "glwidget.h"
#include "ui_mainwindow.h"
#include <QSpinBox>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
{
    ui.setupUi(this);
}
float wind;
float mass;
bool pause;
float xStart;
float yStart;
float radius;
float fps;
bool reopen;
float restitution;
float r, g,b;
float friction;
float drag;

void MainWindow::on_startButton_clicked()
{
    glWidget* bouncingBalls = new glWidget();//start the program and set values
    wind = ui.windBox->value();
    mass = ui.speedBox->value();
    xStart = ui.xPosBox->value();
    radius = ui.radiusBox->value();
    fps = ui.fpsBox->value();
    restitution = ui.colRestBox->value();
    yStart = ui.yPosBox->value();
    r = ui.redBox->value();
    b = ui.blueBox->value();
    g = ui.greenBox->value();
    friction = ui.frictionBox->value();
    drag = ui.dragBox->value();
    if (ui.ballBox->currentText() == "Football"){
        restitution = 0.8;
        ui.colRestBox->setValue(0.8);
        radius = 8;
        ui.radiusBox->setValue(8);
        mass = 5;
        ui.speedBox->setValue(5);
    }
    else if (ui.ballBox->currentText() == "Golf Ball"){
        restitution = 0.5;
        ui.colRestBox->setValue(0.5);
        radius = 2;
        ui.radiusBox->setValue(2);
        mass = 2;
        ui.speedBox->setValue(2);
        r = 10, g= 10, b =10;
        ui.redBox->setValue(10), ui.greenBox->setValue(10), ui.blueBox->setValue(10);
    }
    else if (ui.ballBox->currentText() == "Tennis Ball"){
        restitution = 0.7;
        ui.colRestBox->setValue(0.7);
        radius = 4;
        ui.radiusBox->setValue(4);
        mass = 4;
        ui.speedBox->setValue(4);
        r = 0, g= 10, b =0;
        ui.redBox->setValue(0), ui.greenBox->setValue(10), ui.blueBox->setValue(0);
    }
    bouncingBalls->setDrag(drag);
    bouncingBalls->setFriction(friction);
    bouncingBalls->setColour(r,g,b);
    bouncingBalls->setResitution(restitution);
    bouncingBalls->setFPS(fps);
    bouncingBalls->setWind(wind/1000);
    bouncingBalls->setSpeed(mass/10);
    bouncingBalls->setStartPos(xStart/10,yStart/10);
    bouncingBalls->setRadius(radius/100);
    bouncingBalls->setWindowTitle("Bouncing Balls");
    bouncingBalls->makeCurrent();
    bouncingBalls->show();


}

void MainWindow::on_spinBox_valueChanged(int arg1)
{
}

void MainWindow::on_startButton_2_clicked()
{
    pause = true;
}

void MainWindow::on_startButton_3_clicked()
{
    reopen = true;
}

void MainWindow::on_radiusBox_valueChanged(const QString &arg1)
{

}
