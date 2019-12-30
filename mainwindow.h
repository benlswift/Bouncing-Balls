#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include "ui_mainwindow.h"

QT_BEGIN_NAMESPACE
class  MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = Q_NULLPTR);

private slots:
    void on_startButton_clicked();

    void on_spinBox_valueChanged(int arg1);

    void on_startButton_2_clicked();

    void on_startButton_3_clicked();

    void on_radiusBox_valueChanged(const QString &arg1);

private:
    Ui::MainWindow ui;
};
#endif // MAINWINDOW_H
