#ifndef INTERFACE_HPP
#define INTERFACE_HPP

#include <filesystem>
#include <QtCore/QVariant>
#include <QtWidgets/QAction>
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
#include <QtWidgets/QOpenGLWidget>
#include <QtWidgets/QStatusBar>
#include <QtWidgets/QTabWidget>
#include <QtWidgets/QTableWidget>
#include <QtWidgets/QToolButton>
#include <QtWidgets/QVBoxLayout>
#include <QtWidgets/QWidget>

class interface
{
private:
    QAction *actionload_configuration;
    QAction *actionSave_simulation;
    QAction *actionOpen_simulation;
    QWidget *centralwidget;
    QWidget *horizontalLayoutWidget;
    QHBoxLayout *horizontalLayout;
    QVBoxLayout *verticalLayout_2;
    QGroupBox *groupBox;
    QTableWidget *items;
    QWidget *horizontalLayoutWidget_2;
    QHBoxLayout *horizontalLayout_2;
    QCommandLinkButton *b_remove;
    QCommandLinkButton *b_reset;
    QCommandLinkButton *b_launch;
    QTabWidget *tabWidget;
    QWidget *tab_properties;
    QWidget *formLayoutWidget;
    QFormLayout *formLayout;
    QLabel *label;
    QLineEdit *in_x;
    QLineEdit *in_y;
    QLabel *label_3;
    QLineEdit *in_rotation;
    QLabel *label_4;
    QComboBox *in_animator;
    QLabel *label_2;
    QWidget *tab_4;
    QWidget *gridLayoutWidget;
    QGridLayout *gridLayout_4;
    QToolButton *b_obstacle;
    QToolButton *b_vehicle;
    QOpenGLWidget *openGLWidget;
    QMenuBar *menubar;
    QMenu *menuopen;
    QStatusBar *statusbar;
public:
    std::filesystem::path source;
    interface(/* args */);
    void open();
    void mainloop();
    void setupUi(QMainWindow *MainWindow);
    void retranslateUi(QMainWindow *MainWindow);
    ~interface();
};

namespace ui {
    class MainWindow: public interface {};
}

#endif


