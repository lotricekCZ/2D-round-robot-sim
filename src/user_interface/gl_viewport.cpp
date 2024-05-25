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
	if (keys.size())
	{
		float dy = 1 * (keys.find(Qt::Key_W) != keys.end()) - 1 * (keys.find(Qt::Key_S) != keys.end());
		float dx = 0.01 * (keys.find(Qt::Key_A) != keys.end()) - 0.01 * (keys.find(Qt::Key_D) != keys.end());
		std::for_each(std::execution::par, objects->objects.begin(), objects->objects.end(),
					  [&](auto &o)
					  { 
			if(o->info() == "player"){
				bool collision = false;
				Vect2D move = Vect2D(o->center(), std::get<0>(o->formula()).at(o->rotation() + dx)) / 10 * dy;
				Point2D prediction = o->predict(dx, dy);
				if(std::abs(dy) >= std::numeric_limits<float>::epsilon())
					for(auto p: objects->objects)
						if (o != p)
						{
							Vect2D distance = p->distance(prediction);
							float product = Vect2D::dot(move, distance);
							if ((distance.length() < std::get<0>(o->formula()).radius() /* that'll be circle*/ && product > 0 )) {
								collision = true;
								break;
								};
							
							
						}
				if (collision) return;
				o->move(dx, dy);
				
			} });
	}
	paintGL();
	update();
}

void Viewport::keyPressEvent(QKeyEvent *event)
{
	keys += event->key();
}

void Viewport::keyReleaseEvent(QKeyEvent *event)
{
	keys -= event->key();
}