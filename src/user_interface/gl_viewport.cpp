/**
 * @author Jakub Ramašeuski (xramas01); 2024
 */

#include <QPainter>
#include <QOpenGLWidget>
#include <QOpenGLFunctions>
#include <QSurfaceFormat>
#include <QTimer>
#include <iostream>
#include <memory>
#include "gl_viewport.hpp"
#include "../actors/vehicle.hpp"

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
	setFocusPolicy(Qt::StrongFocus);
	timer->start(37);
}

void Viewport::initializeGL()
{
	initializeOpenGLFunctions();
	glViewport(0, 0, QWidget::width(), QWidget::height());
	glMatrixMode(GL_PROJECTION);
	float aspect = (float)QWidget::width() / (float)QWidget::height();
	glOrtho(-aspect, aspect, -1, 1, -1, 1);
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
		obstacle o;
		o.place(0.4, 0.3);
		objects.add(std::make_shared<obstacle>(o));
		o.place(-0.4, 0.3);
		o.rotate(-0.25);
		objects.add(std::make_shared<obstacle>(o));
		o.place(-0.4, -0.3);
		objects.add(std::make_shared<obstacle>(o));
		o.place(0.4, -0.3);
		o.rotate(0.25);
		objects.add(std::make_shared<obstacle>(o));
}

void Viewport::paintGL()
{
	glClearColor(0.5f, 0.5f, 0.8f, 0.0f);
	glClear(GL_COLOR_BUFFER_BIT);

	objects.render();
	v.render();

	glFlush();
}

void Viewport::animate()
{
	paintGL();
	update();
}

void Viewport::keyPressEvent(QKeyEvent * event){
	int key = event->key();
	printf("key pressed: %c\n", (char)key);
	v.move(-0.02 * (key == Qt::Key_A) + 0.02 * (key == Qt::Key_D), 0.02 * (key == Qt::Key_W) - 0.02 * (key == Qt::Key_S));
}