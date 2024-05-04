/**
 * @author Jakub Ramašeuski (xramas01); 2024
 */

#include <QPainter>
#include <QOpenGLWidget>
#include <QOpenGLFunctions>
#include <QSurfaceFormat>
#include "gl_viewport.hpp"

Viewport::~Viewport(){}

Viewport::Viewport(QWidget *parent) : QOpenGLWidget(parent)
{
	QSurfaceFormat format;
	format.setDepthBufferSize(24);
	format.setStencilBufferSize(8);
	format.setVersion(3, 2);
	format.setProfile(QSurfaceFormat::CoreProfile);
	QSurfaceFormat::setDefaultFormat(format);
}

void Viewport::initializeGL()
{
	initializeOpenGLFunctions();
}

void Viewport::paintGL()
{
	glClearColor(0.5f, 0.5f, 0.8f, 0.0f);
	glClear(GL_COLOR_BUFFER_BIT);

	glBegin(GL_POLYGON);

	glColor3f(1.0f, 0.0f, 1.0f);

	glVertex2f(-0.5f, -0.5f);
	glVertex2f(0.5f, -0.5f);
	glVertex2f(0.5f, 0.5f);
	glVertex2f(0.2f, 0.0f);
	glVertex2f(-0.5f, 0.5f);

	glEnd();
	glFlush();
}