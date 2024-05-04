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
#include <QtWidgets/QStatusBar>
#include <QtWidgets/QTabWidget>
#include <QtWidgets/QTableWidget>
#include <QtWidgets/QToolButton>
#include <QtWidgets/QVBoxLayout>
#include <QtWidgets/QWidget>
#include <QKeyEvent>
#include <QUiLoader>
#include "gl_viewport.hpp"

class interface : public QMainWindow
{
private:
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
    QToolButton *b_obstacle;
    QToolButton *b_vehicle;
    Viewport *openGL_widget;
    QMenuBar *menubar;
    QMenu *menuopen;
    QStatusBar *statusbar;
    
public:
    
    interface();
    void open();
    void mainloop();
    using QMainWindow::show;
    void setupUi(QMainWindow *MainWindow);
    void retranslateUi(QMainWindow *MainWindow);
    ~interface();

protected:
    void keyPressEvent(QKeyEvent *event) override
    {
        if (event->type() == QEvent::KeyPress)
        {
            // Přetypujeme událost na klávesovou událost
            QKeyEvent *keyEvent = static_cast<QKeyEvent *>(event);

            // Získáme kód stisknuté klávesy
            int key = keyEvent->key();

            // Zkontrolujeme, zda byla stisknuta klávesa Enter
            if (key == Qt::Key_Enter || key == Qt::Key_Return)
            {
                printf("Stisknuta klávesa Enter\n");
            }
            else
            {
                // Pokud ne, zobrazíme text odpovídající klávesu
                printf("Stisknuta klávesa: %d\n", keyEvent->key());
            }
        }
    }
};

namespace ui
{
    class MainWindow : public interface
    {
    };
}

#endif
