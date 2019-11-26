//#include "mainwindow.h"
//#include "GL/glut.h"

//MainWindow::MainWindow(QWidget *parent)
//{
//    setSurfaceType(QWindow::OpenGLSurface);
//    QSurfaceFormat format;
//    format.setProfile(QSurfaceFormat::CompatibilityProfile);
//    format.setVersion(2,1);
//    setFormat(format);

//    context = new QOpenGLContext;
//    context->setFormat(format);
//    context->create();
//    context->makeCurrent(this);

//    openGLFunctions = context->functions();

//}

//MainWindow::~MainWindow()
//{

//}

//void MainWindow::initializeGL()
//{

//    resizeGL(this->width(),this->height());
//}

//void MainWindow::resizeGL(int w, int h)
//{
//    glMatrixMode(GL_PROJECTION);
//    glLoadIdentity();
//    glViewport(0,0,w,h);

//    qreal aspectRatio = qreal(w) / qreal(h);
//    glOrtho(-1 * aspectRatio, 1 * aspectRatio,-1,1,1,-1);


//}

//void MainWindow::paintGL()
//{
//    glClearColor(0.0f,0.0f,0.0f,0.0f);
//    glClear(GL_COLOR_BUFFER_BIT);

//    glBegin(GL_QUADS);

//    glColor3f(1.0f,0.0f,0.0f);
//    glVertex2f(-0.5f,-0.5f);
//    glColor3f(0.0f,1.0f,0.0f);
//    glVertex2f(0.5f,-0.5f);
//    glColor3f(0.0f,0.0f,1.0f);
//    glVertex2f(0.5f,0.5f);
//    glColor3f(0.5f,0.5f,0.5f);
//    glVertex2f(-0.5f,0.5f);
//    glEnd();

//    glBegin(GL_TRIANGLES);

//    glColor3f(1.0f,0.0f,0.0f);
//    glVertex2f(-0.4f,-0.4f);
//    glColor3f(1.0f,0.0f,0.0f);
//    glVertex2f(0.8f,-0.1f);
//    glColor3f(1.0f,0.0f,0.0f);
//    glVertex2f(-0.1f,-0.8f);



//    glEnd();
//    glFlush();
//}

//void MainWindow::resizeEvent(QResizeEvent *event)
//{
//    resizeGL(this->width(), this->height());
//    this->update();
//}

//void MainWindow::paintEvent(QPaintEvent *event)
//{
//    paintGL();
//}
/****************************************************************************
**
** Copyright (C) 2016 The Qt Company Ltd.
** Contact: https://www.qt.io/licensing/
**
** This file is part of the examples of the Qt Toolkit.
**
** $QT_BEGIN_LICENSE:BSD$
** Commercial License Usage
** Licensees holding valid commercial Qt licenses may use this file in
** accordance with the commercial license agreement provided with the
** Software or, alternatively, in accordance with the terms contained in
** a written agreement between you and The Qt Company. For licensing terms
** and conditions see https://www.qt.io/terms-conditions. For further
** information use the contact form at https://www.qt.io/contact-us.
**
** BSD License Usage
** Alternatively, you may use this file under the terms of the BSD license
** as follows:
**
** "Redistribution and use in source and binary forms, with or without
** modification, are permitted provided that the following conditions are
** met:
**   * Redistributions of source code must retain the above copyright
**     notice, this list of conditions and the following disclaimer.
**   * Redistributions in binary form must reproduce the above copyright
**     notice, this list of conditions and the following disclaimer in
**     the documentation and/or other materials provided with the
**     distribution.
**   * Neither the name of The Qt Company Ltd nor the names of its
**     contributors may be used to endorse or promote products derived
**     from this software without specific prior written permission.
**
**
** THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS
** "AS IS" AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT
** LIMITED TO, THE IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR
** A PARTICULAR PURPOSE ARE DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT
** OWNER OR CONTRIBUTORS BE LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL,
** SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT
** LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE,
** DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY
** THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT
** (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE
** OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE."
**
** $QT_END_LICENSE$
**
****************************************************************************/

#include "mainwindow.h"
#include "window.h"
#include <QMenuBar>
#include <QMenu>
#include <QMessageBox>

MainWindow::MainWindow()
{
    QMenuBar *menuBar = new QMenuBar;
    QMenu *menuWindow = menuBar->addMenu(tr("&Window"));
    QAction *addNew = new QAction(menuWindow);
    addNew->setText(tr("Add new"));
    menuWindow->addAction(addNew);
    connect(addNew, &QAction::triggered, this, &MainWindow::onAddNew);
    setMenuBar(menuBar);

    onAddNew();
}

void MainWindow::onAddNew()
{
    if (!centralWidget())
        setCentralWidget(new Window(this));
    else
        QMessageBox::information(0, tr("Cannot add new window"), tr("Already occupied. Undock first."));
}

