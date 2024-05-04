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

#ifndef GL_VIEWPORT_HPP
#define GL_VIEWPORT_HPP
class Helper;

class Viewport : public QOpenGLWidget, public QOpenGLFunctions
{
    // Q_OBJECT
public:
    Viewport(QWidget *parent = nullptr);
    QTimer *timer;
    Viewport() = delete;
    ~Viewport();
public slots:
    void animate();
protected:
    void timerEvent(QTimerEvent *event) override;
    void initializeGL() override;
    void paintGL() override;
private:
    float move = 1;
    Helper *helper;
    int elapsed;
};

#endif