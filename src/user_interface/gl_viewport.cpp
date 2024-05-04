/**
 * @author Jakub Ramašeuski (xramas01); 2024
 */

#include <QPainter>
#include <QOpenGLWidget>
#include <QOpenGLFunctions>
#include <QSurfaceFormat>
#include <QTimer>
#include <iostream>
#include "gl_viewport.hpp"

Viewport::~Viewport() {}

Viewport::Viewport(QWidget *parent) : QOpenGLWidget(parent)
{
	QSurfaceFormat format;
	this->timer = new QTimer(this);
	format.setDepthBufferSize(24);
	format.setStencilBufferSize(8);
	format.setVersion(3, 2);
	format.setProfile(QSurfaceFormat::CoreProfile);
	QSurfaceFormat::setDefaultFormat(format);
	connect(timer, &QTimer::timeout, this, &Viewport::animate);
	
	timer->start(37);
}

void Viewport::initializeGL()
{
	initializeOpenGLFunctions();
}

void Viewport::paintGL()
{
	glClearColor(0.5f, 0.5f, 0.8f, 0.0f);
	glClear(GL_COLOR_BUFFER_BIT);
	glColor3f(1.0f, 0.0f, 1.0f);

	glRotatef(move, 0.0, 0.0, 1.0);
	glBegin(GL_POLYGON);


	glVertex2f(-0.5f, -0.5f);
	glVertex2f(0.5f, -0.5f);
	glVertex2f(0.5f, 0.5f);
	glVertex2f(0.2f, 0.0f);
	glVertex2f(-0.5f, 0.5f);

	glEnd();
	glFlush();
	// move += 0.1;
}

void Viewport::timerEvent(QTimerEvent *)
{
}

void Viewport::animate(){
	// std::cout << "timer" << std::endl;
	paintGL();
	update();
}