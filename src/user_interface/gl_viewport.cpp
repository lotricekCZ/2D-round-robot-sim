/**
 * @author Jakub Ramašeuski (xramas01); 2024
 */

#include <QPainter>
#include <QBuffer>
#include <QOpenGLWidget>
#include <QGLWidget>
#include <QOpenGLFunctions>
#include <QSurfaceFormat>
#include <QTimer>
#include <iostream>
#include <memory>
#include <execution>
#include <algorithm>
#include <ctime>
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
	QFile vertex_file("src/user_interface/vertex_shader.glsl");
	QFile fragment_file("src/user_interface/fragment_shader.glsl");
	char *source;
	QByteArray ba;
	if (vertex_file.open(QIODevice::ReadOnly | QIODevice::Text))
	{
		ba = vertex_file.readAll();
		source = ba.data();
		vertex_file.close();
	}
	GLuint vshader = glCreateShader(GL_VERTEX_SHADER);
	glShaderSource(vshader, 1, (const char **)&source, NULL); // vertex_shader_source is a GLchar* containing glsl shader source code
	glCompileShader(vshader);

	GLint compiled;
	glGetShaderiv(vshader, GL_COMPILE_STATUS, &compiled);
	if (compiled != GL_TRUE)
	{
		GLsizei log_length = 0;
		GLchar message[2048];
		glGetShaderInfoLog(vshader, 2048, &log_length, message);
	}

	if (fragment_file.open(QIODevice::ReadOnly | QIODevice::Text))
	{
		ba = fragment_file.readAll();
		source = ba.data();
		fragment_file.close();
	}
	GLuint fshader = glCreateShader(GL_FRAGMENT_SHADER);
	glShaderSource(fshader, 1, (const char **)&source, NULL);
	glCompileShader(fshader);

	glGetShaderiv(fshader, GL_COMPILE_STATUS, &compiled);
	if (compiled != GL_TRUE)
	{
		GLsizei log_length = 0;
		GLchar message[2048];
		glGetShaderInfoLog(fshader, 2048, &log_length, message);
	}
	// shader thingy end
	program = glCreateProgram();
	glAttachShader(program, vshader);
	glAttachShader(program, fshader);
	glLinkProgram(program);

	GLint program_linked;
	glGetProgramiv(program, GL_LINK_STATUS, &program_linked);
	if (program_linked != GL_TRUE)
	{
		GLsizei log_length = 0;
		GLchar message[1024];
		glGetProgramInfoLog(program, 1024, &log_length, message);
	}
	glViewport(0, 0, QWidget::width(), QWidget::height());
	glUseProgram(program);
	m_proj = glGetUniformLocation(program, "u_proj");
	f_time = glGetUniformLocation(program, "u_time");
	GLfloat proj_m[4][4] = {0};
	{
		float left = -(float)QWidget::width() / (float)QWidget::height();
		float right = -left,
			  bottom = -1,
			  top = 1,
			  nearVal = -1,
			  farVal = 1;
		proj_m[0][0] = 2.0f / (right - left);
		proj_m[1][1] = 2.0f / (top - bottom);
		proj_m[2][2] = -2.0f / (farVal - nearVal);
		proj_m[3][3] = 1.0f;

		proj_m[0][3] = -(right + left) / (right - left);
		proj_m[1][3] = -(top + bottom) / (top - bottom);
		proj_m[2][3] = -(farVal + nearVal) / (farVal - nearVal);
	}

	glUniformMatrix4fv(m_proj, 1, GL_FALSE, &proj_m[0][0]);
	// glLoadIdentity();
	QImage img("src/user_interface/vehicle.png");
	QImage tex = QGLWidget::convertToGLFormat(img);
	unsigned char *texture_img = img.bits();
	int width = tex.width();
	int height = tex.height();
	printf("%d\t%d\n", width, height);
	glEnable(GL_TEXTURE_2D);
	glGenTextures(1, &texture_id);
	glBindTexture(GL_TEXTURE_2D, texture_id);
	glPixelStorei(GL_UNPACK_ALIGNMENT, 1);
	glTexEnvf(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_DECAL);

	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, tex.width(), tex.height(), 0, GL_RGBA, GL_UNSIGNED_BYTE, tex.bits());

	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);

	glUniform1i(glGetUniformLocation(program, "vehicle_texture"), 0);
	glDisable(GL_TEXTURE_2D);
	glUseProgram(program);
	// This step is unnecessary if you use the location specifier in your shader
	// e.g. layout (location = 0) in vec3 position;
	// glBindAttribLocation(program, 0, "vPos");
	// glBindAttribLocation(program, 1, "vColor");
	// glBindAttribLocation(program, 2, "vTexCoord");
}

void Viewport::paintGL()
{
	glClearColor(0.5f, 0.5f, 0.8f, 0.0f);
	glClear(GL_COLOR_BUFFER_BIT);
	// glActiveTexture(GL_TEXTURE0); // activate the texture unit first before binding texture
	// glBindTexture(GL_TEXTURE_2D, texture_id);
	struct timespec spec;
	clock_gettime(CLOCK_REALTIME, &spec);
	// s  = spec.tv_sec;
	// ms = round(spec.tv_nsec / 1.0e6);
	glUniform1f(f_time, spec.tv_nsec / 5e8);
	glEnable(GL_TEXTURE_2D);
	glBindTexture(GL_TEXTURE_2D, texture_id);
	objects->render();
	glDisable(GL_TEXTURE_2D);

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

unsigned char *Viewport::load_vehicle(int &size)
{
	QImage image("src/user_interface/vehicle.bmp");
	QByteArray bytes;
	QBuffer buffer(&bytes);
	buffer.open(QIODevice::WriteOnly);
	image.save(&buffer, "BMP");
	buffer.close();

	unsigned char *data = (unsigned char *)malloc(bytes.size());
	memcpy(data, reinterpret_cast<unsigned char *>(bytes.data()), bytes.size());
	size = bytes.size();
	return data;
}