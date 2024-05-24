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
#include <execution>
#include <algorithm>
#include "gl_viewport.hpp"
#include "../actors/vehicle.hpp"

Viewport::~Viewport() {}

Viewport::Viewport(QWidget *parent, std::shared_ptr<renderer> objs) : QOpenGLWidget(parent)
{
	QSurfaceFormat format;
	this->objects = objs;
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
}

void Viewport::paintGL()
{
	glClearColor(0.5f, 0.5f, 0.8f, 0.0f);
	glClear(GL_COLOR_BUFFER_BIT);

	objects->render();

	glFlush();
}

void Viewport::animate()
{
	paintGL();
	update();
}

void Viewport::keyPressEvent(QKeyEvent *event)
{
	keysPressed += event->key();
	std::for_each(std::execution::par, objects->objects.begin(), objects->objects.end(),
				  [&](auto &o)
				  { 
					if(o->info() == "player")
					o->move(0.01 * (keysPressed.find(Qt::Key_A) != keysPressed.end()) - 0.01 * (keysPressed.find(Qt::Key_D) != keysPressed.end()), 1 * (keysPressed.find(Qt::Key_W) != keysPressed.end()) - 1 * (keysPressed.find(Qt::Key_S) != keysPressed.end())); });
}

void Viewport::keyReleaseEvent(QKeyEvent *event)
{
	keysPressed -= event->key();
	for (auto k: keysPressed)
	{
		std::cout << k << std::endl;
	}
	std::cout << std::endl;
	std::for_each(std::execution::par, objects->objects.begin(), objects->objects.end(),
				  [&](auto &o)
				  { 
					if(o->info() == "player")
					o->move(0.01 * (keysPressed.find(Qt::Key_A) != keysPressed.end()) - 0.01 * (keysPressed.find(Qt::Key_D) != keysPressed.end()), 1 * (keysPressed.find(Qt::Key_W) != keysPressed.end()) - 1 * (keysPressed.find(Qt::Key_S) != keysPressed.end())); });
}