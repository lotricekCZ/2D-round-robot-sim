/**
 * @author Jakub Ramašeuski (xramas01); 2024
 */

#include <QtWidgets/QOpenGLWidget>
#include <QtWidgets/QApplication>
#include <QtWidgets/QComboBox>
#include <QtWidgets/QCommandLinkButton>
#include <QtWidgets/QFormLayout>
#include <QtWidgets/QGridLayout>
#include <QtWidgets/QGroupBox>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QLabel>
#include <QtWidgets/QLineEdit>
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QMenu>
#include <QtWidgets/QMenuBar>
#include <QtWidgets/QStatusBar>
#include <QtWidgets/QTabWidget>
#include <QtWidgets/QTableWidget>
#include <QtWidgets/QToolButton>
#include <QtWidgets/QVBoxLayout>
#include <QtWidgets/QWidget>
#include <QKeyEvent>
#include <QUiLoader>
#include <QOpenGLFunctions>
#include <QOpenGLShaderProgram>
#include "../actors/vehicle.hpp"
#include "../actors/obstacle.hpp"
#include "../renderable/renderer.hpp"

#ifndef GL_VIEWPORT_HPP
#define GL_VIEWPORT_HPP

class Viewport : public QOpenGLWidget, public QOpenGLFunctions
{
    // Q_OBJECT
public:
    vehicle v, b;
    std::shared_ptr<renderer> objects;
    Viewport(QWidget *parent = nullptr, std::shared_ptr<renderer> objs = nullptr);
    QTimer *timer;
    Viewport() = delete;
    ~Viewport();
public slots:
    void animate();
    void keyPressEvent(QKeyEvent *event);

protected:
    void initializeGL() override;
    void paintGL() override;

private:
};

#endif