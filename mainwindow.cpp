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

void MainWindow::on_startButton_clicked()
{
    glWidget* bouncingBalls = new glWidget();//start the program and set values
    wind = ui.windBox->value();
    mass = ui.speedBox->value();
    xStart = ui.xPosBox->value();
    radius = ui.radiusBox->value();
    fps = ui.fpsBox->value();
    restitution = ui.colRestBox->value();
    if (ui.ballBox->currentText() == "Football"){
        restitution = 8;
        ui.colRestBox->setValue(8);
        radius = 8;
        ui.radiusBox->setValue(8);
        mass = 5;
        ui.speedBox->setValue(5);
    }
    bouncingBalls->setResitution(restitution);
    bouncingBalls->setFPS(fps);
    bouncingBalls->setWind(wind/1000);
    bouncingBalls->setSpeed(mass/10);
    bouncingBalls->setStartPos(xStart/10,0.8f);
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
