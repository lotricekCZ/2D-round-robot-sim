/**
 * @author Jakub Ramašeuski (xramas01); 2024
 */

#ifndef INTERFACE_HPP
#define INTERFACE_HPP

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
#include <QtWidgets/QStatusBar>
#include <QtWidgets/QTabWidget>
#include <QtWidgets/QTableWidget>
#include <QtWidgets/QToolButton>
#include <QtWidgets/QVBoxLayout>
#include <QtWidgets/QWidget>
#include <QTimer>
#include <QKeyEvent>
#include <QDoubleValidator>
#include "gl_viewport.hpp"
#include "serializer.hpp"
#include "../actors/player.hpp"

class interface : public QMainWindow
{
    Q_OBJECT
private:
    // input validators
    QDoubleValidator *coords_validator; // (double bottom, double top, int decimals, QObject *parent = nullptr)
    QDoubleValidator *rotation_validator;
    // misc
    QAction *actionload_configuration;
    QAction *actionSave_simulation;
    QAction *actionOpen_simulation;
    QWidget *centralwidget;
    QWidget *horizontal_layout_widget;
    QHBoxLayout *horizontal_layout;
    QVBoxLayout *vertical_layout_2;
    QGroupBox *group_box;
    QTableWidget *items;
    QWidget *horizontal_layout_widget_2;
    QHBoxLayout *horizontal_layout_2;
    QCommandLinkButton *b_remove;
    QCommandLinkButton *b_reset;
    QCommandLinkButton *b_launch;
    QWidget *tab_properties;
    QWidget *form_layout_widget;
    QFormLayout *form_layout;
    QTabWidget *tab_widget;

    // inputs
    QLabel *l_x;
    QLineEdit *in_x;
    QLabel *l_y;
    QLineEdit *in_y;
    QLabel *l_r;
    QLineEdit *in_rotation;
    QLabel *l_a;
    QComboBox *in_animator;

    QWidget *tab_4;
    QWidget *grid_layout_widget;
    QGridLayout *grid_layout_4;
    QPushButton *b_obstacle;
    QPushButton *b_vehicle;
    Viewport *openGL_widget;
    QMenuBar *menubar;
    QMenu *menuopen;
    QStatusBar *statusbar;

    // timers
    QTimer *timer_table;
    int selected;
    Serializer serializer;
    std::shared_ptr<renderer> rndr;

public:
    interface();
    void open();
    void mainloop();
    using QMainWindow::show;
    void setupUi(QMainWindow *MainWindow);
    void retranslateUi(QMainWindow *MainWindow);
    ~interface();
public slots:
    void update_table();
    void assign_animator(QString s) const { printf("selected: %s\n", s.toStdString().c_str()); }
    void change_x(QString s) const { printf("x: %s\n", s.toStdString().c_str()); }
    void change_y(QString s) const { printf("y: %s\n", s.toStdString().c_str()); }
    void change_rotation(QString s) const { printf("y: %s\n", s.toStdString().c_str()); }

protected:
};

namespace ui
{
    class MainWindow : public interface
    {
    };
}

#endif
