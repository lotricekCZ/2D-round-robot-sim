/**
 * @author Jakub Ramašeuski (xramas01); 2024
*/
#include "interface.hpp"

interface::interface() : QMainWindow()
{
	this->installEventFilter(this);
	setupUi(this);
	setFocusPolicy(Qt::StrongFocus);
}
void interface::open()
{
}
void interface::mainloop()
{
}
interface::~interface()
{
}

void interface::setupUi(QMainWindow *MainWindow)
{
	if (MainWindow->objectName().isEmpty())
		MainWindow->setObjectName(QString::fromUtf8("MainWindow"));
	MainWindow->resize(1195, 758);
	actionload_configuration = new QAction(MainWindow);
	actionload_configuration->setObjectName(QString::fromUtf8("actionload_configuration"));
	actionSave_simulation = new QAction(MainWindow);
	actionSave_simulation->setObjectName(QString::fromUtf8("actionSave_simulation"));
	actionOpen_simulation = new QAction(MainWindow);
	actionOpen_simulation->setObjectName(QString::fromUtf8("actionOpen_simulation"));
	centralwidget = new QWidget(MainWindow);
	centralwidget->setObjectName(QString::fromUtf8("centralwidget"));
	horizontal_layout_widget = new QWidget(centralwidget);
	horizontal_layout_widget->setObjectName(QString::fromUtf8("horizontal_layout_widget"));
	horizontal_layout_widget->setGeometry(QRect(0, 0, 1234, 722));
	horizontal_layout = new QHBoxLayout(horizontal_layout_widget);
	horizontal_layout->setObjectName(QString::fromUtf8("horizontal_layout"));
	horizontal_layout->setContentsMargins(0, 0, 0, 0);
	vertical_layout_2 = new QVBoxLayout();
	vertical_layout_2->setObjectName(QString::fromUtf8("vertical_layout_2"));
	group_box = new QGroupBox(horizontal_layout_widget);
	group_box->setObjectName(QString::fromUtf8("group_box"));
	QSizePolicy sizePolicy(QSizePolicy::Preferred, QSizePolicy::Preferred);
	sizePolicy.setHorizontalStretch(0);
	sizePolicy.setVerticalStretch(1);
	sizePolicy.setHeightForWidth(group_box->sizePolicy().hasHeightForWidth());
	group_box->setSizePolicy(sizePolicy);
	group_box->setMinimumSize(QSize(400, 0));
	group_box->setMaximumSize(QSize(16777215, 300));
	group_box->setSizeIncrement(QSize(1, 1));
	items = new QTableWidget(group_box);
	items->setObjectName(QString::fromUtf8("items"));
	items->setGeometry(QRect(0, 20, 400, 220));
	horizontal_layout_widget_2 = new QWidget(group_box);
	horizontal_layout_widget_2->setObjectName(QString::fromUtf8("horizontal_layout_widget_2"));
	horizontal_layout_widget_2->setGeometry(QRect(0, 239, 401, 61));
	horizontal_layout_2 = new QHBoxLayout(horizontal_layout_widget_2);
	horizontal_layout_2->setObjectName(QString::fromUtf8("horizontal_layout_2"));
	horizontal_layout_2->setSizeConstraint(QLayout::SetMaximumSize);
	horizontal_layout_2->setContentsMargins(0, 0, 0, 0);
	b_remove = new QCommandLinkButton(horizontal_layout_widget_2);
	b_remove->setObjectName(QString::fromUtf8("b_remove"));
	b_remove->setMaximumSize(QSize(150, 16777215));
	b_remove->setSizeIncrement(QSize(0, 0));

	horizontal_layout_2->addWidget(b_remove);

	b_reset = new QCommandLinkButton(horizontal_layout_widget_2);
	b_reset->setObjectName(QString::fromUtf8("b_reset"));
	b_reset->setMaximumSize(QSize(80, 16777215));
	b_reset->setSizeIncrement(QSize(0, 0));

	horizontal_layout_2->addWidget(b_reset);

	b_launch = new QCommandLinkButton(horizontal_layout_widget_2);
	b_launch->setObjectName(QString::fromUtf8("b_launch"));
	b_launch->setMaximumSize(QSize(80, 16777215));
	b_launch->setSizeIncrement(QSize(0, 0));

	horizontal_layout_2->addWidget(b_launch);

	vertical_layout_2->addWidget(group_box);

	tab_widget = new QTabWidget(horizontal_layout_widget);
	tab_widget->setObjectName(QString::fromUtf8("tab_widget"));
	tab_properties = new QWidget();
	tab_properties->setObjectName(QString::fromUtf8("tab_properties"));
	form_layout_widget = new QWidget(tab_properties);
	form_layout_widget->setObjectName(QString::fromUtf8("form_layout_widget"));
	form_layout_widget->setGeometry(QRect(-1, -1, 401, 131));
	form_layout = new QFormLayout(form_layout_widget);
	form_layout->setObjectName(QString::fromUtf8("form_layout"));
	form_layout->setLabelAlignment(Qt::AlignCenter);
	form_layout->setContentsMargins(18, 0, 0, 0);
	l_x = new QLabel(form_layout_widget);
	l_x->setObjectName(QString::fromUtf8("l_x"));
	QSizePolicy sizePolicy1(QSizePolicy::Preferred, QSizePolicy::Preferred);
	sizePolicy1.setHorizontalStretch(0);
	sizePolicy1.setVerticalStretch(0);
	sizePolicy1.setHeightForWidth(l_x->sizePolicy().hasHeightForWidth());
	l_x->setSizePolicy(sizePolicy1);
	l_x->setMinimumSize(QSize(100, 0));
	l_x->setAlignment(Qt::AlignCenter);
	l_x->setMargin(1);

	form_layout->setWidget(0, QFormLayout::LabelRole, l_x);

	in_x = new QLineEdit(form_layout_widget);
	in_x->setObjectName(QString::fromUtf8("in_x"));
	in_x->setMinimumSize(QSize(0, 0));
	in_x->setMaximumSize(QSize(200, 16777215));

	form_layout->setWidget(0, QFormLayout::FieldRole, in_x);

	in_y = new QLineEdit(form_layout_widget);
	in_y->setObjectName(QString::fromUtf8("in_y"));
	in_y->setMaximumSize(QSize(200, 16777215));
	in_y->setSizeIncrement(QSize(0, 0));

	form_layout->setWidget(1, QFormLayout::FieldRole, in_y);

	l_r = new QLabel(form_layout_widget);
	l_r->setObjectName(QString::fromUtf8("l_r"));
	l_r->setMinimumSize(QSize(100, 0));
	l_r->setAlignment(Qt::AlignCenter);

	form_layout->setWidget(2, QFormLayout::LabelRole, l_r);

	in_rotation = new QLineEdit(form_layout_widget);
	in_rotation->setObjectName(QString::fromUtf8("in_rotation"));
	in_rotation->setMaximumSize(QSize(200, 16777215));

	form_layout->setWidget(2, QFormLayout::FieldRole, in_rotation);

	l_a = new QLabel(form_layout_widget);
	l_a->setObjectName(QString::fromUtf8("l_a"));

	form_layout->setWidget(3, QFormLayout::LabelRole, l_a);

	in_animator = new QComboBox(form_layout_widget);
	in_animator->addItem(QString());
	in_animator->addItem(QString());
	in_animator->setObjectName(QString::fromUtf8("in_animator"));
	QSizePolicy sizePolicy2(QSizePolicy::Minimum, QSizePolicy::Fixed);
	sizePolicy2.setHorizontalStretch(0);
	sizePolicy2.setVerticalStretch(0);
	sizePolicy2.setHeightForWidth(in_animator->sizePolicy().hasHeightForWidth());
	in_animator->setSizePolicy(sizePolicy2);
	in_animator->setMinimumSize(QSize(200, 0));
	in_animator->setMaximumSize(QSize(200, 16777215));

	form_layout->setWidget(3, QFormLayout::FieldRole, in_animator);

	l_y = new QLabel(form_layout_widget);
	l_y->setObjectName(QString::fromUtf8("l_y"));
	QSizePolicy sizePolicy3(QSizePolicy::Fixed, QSizePolicy::Fixed);
	sizePolicy3.setHorizontalStretch(0);
	sizePolicy3.setVerticalStretch(1);
	sizePolicy3.setHeightForWidth(l_y->sizePolicy().hasHeightForWidth());
	l_y->setSizePolicy(sizePolicy3);
	l_y->setMinimumSize(QSize(100, 0));
	l_y->setAlignment(Qt::AlignCenter);

	form_layout->setWidget(1, QFormLayout::LabelRole, l_y);

	tab_widget->addTab(tab_properties, QString());
	tab_4 = new QWidget();
	tab_4->setObjectName(QString::fromUtf8("tab_4"));
	grid_layout_widget = new QWidget(tab_4);
	grid_layout_widget->setObjectName(QString::fromUtf8("grid_layout_widget"));
	grid_layout_widget->setGeometry(QRect(10, 9, 381, 71));
	grid_layout_4 = new QGridLayout(grid_layout_widget);
	grid_layout_4->setObjectName(QString::fromUtf8("grid_layout_4"));
	grid_layout_4->setSizeConstraint(QLayout::SetMinimumSize);
	grid_layout_4->setContentsMargins(0, 0, 0, 0);
	b_obstacle = new QToolButton(grid_layout_widget);
	b_obstacle->setObjectName(QString::fromUtf8("b_obstacle"));
	b_obstacle->setMinimumSize(QSize(50, 50));

	grid_layout_4->addWidget(b_obstacle, 0, 1, 1, 1);

	b_vehicle = new QToolButton(grid_layout_widget);
	b_vehicle->setObjectName(QString::fromUtf8("b_vehicle"));
	b_vehicle->setMinimumSize(QSize(50, 50));

	grid_layout_4->addWidget(b_vehicle, 0, 0, 1, 1);

	tab_widget->addTab(tab_4, QString());

	vertical_layout_2->addWidget(tab_widget);

	horizontal_layout->addLayout(vertical_layout_2);

	openGL_widget = new Viewport(horizontal_layout_widget);
	openGL_widget->setObjectName(QString::fromUtf8("openGL_widget"));
	QSizePolicy sizePolicy4(QSizePolicy::Expanding, QSizePolicy::Expanding);
	sizePolicy4.setHorizontalStretch(1);
	sizePolicy4.setVerticalStretch(1);
	sizePolicy4.setHeightForWidth(openGL_widget->sizePolicy().hasHeightForWidth());
	openGL_widget->setSizePolicy(sizePolicy4);
	openGL_widget->setMinimumSize(QSize(824, 720));
	openGL_widget->setSizeIncrement(QSize(1, 1));

	horizontal_layout->addWidget(openGL_widget);

	MainWindow->setCentralWidget(centralwidget);
	menubar = new QMenuBar(MainWindow);
	menubar->setObjectName(QString::fromUtf8("menubar"));
	menubar->setGeometry(QRect(0, 0, 1195, 22));
	menuopen = new QMenu(menubar);
	menuopen->setObjectName(QString::fromUtf8("menuopen"));
	MainWindow->setMenuBar(menubar);
	statusbar = new QStatusBar(MainWindow);
	statusbar->setObjectName(QString::fromUtf8("statusbar"));
	MainWindow->setStatusBar(statusbar);
	QWidget::setTabOrder(items, b_remove);
	QWidget::setTabOrder(b_remove, b_reset);
	QWidget::setTabOrder(b_reset, b_launch);

	menubar->addAction(menuopen->menuAction());
	menuopen->addAction(actionload_configuration);
	menuopen->addAction(actionSave_simulation);
	menuopen->addAction(actionOpen_simulation);

	retranslateUi(MainWindow);

	tab_widget->setCurrentIndex(0);

	QMetaObject::connectSlotsByName(MainWindow);
} // setupUi

void interface::retranslateUi(QMainWindow *MainWindow)
{
	MainWindow->setWindowTitle(QCoreApplication::translate("MainWindow", "ICP project", nullptr));
	actionload_configuration->setText(QCoreApplication::translate("MainWindow", "New simulation", nullptr));
#if QT_CONFIG(shortcut)
	actionload_configuration->setShortcut(QCoreApplication::translate("MainWindow", "Ctrl+N", nullptr));
#endif // QT_CONFIG(shortcut)
	actionSave_simulation->setText(QCoreApplication::translate("MainWindow", "Save simulation", nullptr));
#if QT_CONFIG(shortcut)
	actionSave_simulation->setShortcut(QCoreApplication::translate("MainWindow", "Ctrl+S", nullptr));
#endif // QT_CONFIG(shortcut)
	actionOpen_simulation->setText(QCoreApplication::translate("MainWindow", "Open simulation", nullptr));
#if QT_CONFIG(shortcut)
	actionOpen_simulation->setShortcut(QCoreApplication::translate("MainWindow", "Ctrl+O", nullptr));
#endif // QT_CONFIG(shortcut)
	group_box->setTitle(QCoreApplication::translate("MainWindow", "Map elements", nullptr));
	b_remove->setText(QCoreApplication::translate("MainWindow", "Remove element", nullptr));
#if QT_CONFIG(shortcut)
	b_remove->setShortcut(QCoreApplication::translate("MainWindow", "Del", nullptr));
#endif // QT_CONFIG(shortcut)
	b_reset->setText(QCoreApplication::translate("MainWindow", "Reset", nullptr));
	b_launch->setText(QCoreApplication::translate("MainWindow", "Launch", nullptr));
#if QT_CONFIG(shortcut)
	b_launch->setShortcut(QCoreApplication::translate("MainWindow", "F5", nullptr));
#endif // QT_CONFIG(shortcut)
	l_x->setText(QCoreApplication::translate("MainWindow", "x", nullptr));
	l_r->setText(QCoreApplication::translate("MainWindow", "rotation [\302\260]", nullptr));
	l_a->setText(QCoreApplication::translate("MainWindow", "Animator", nullptr));
	in_animator->setItemText(0, QCoreApplication::translate("MainWindow", "User", nullptr));
	in_animator->setItemText(1, QCoreApplication::translate("MainWindow", "AI", nullptr));

	l_y->setText(QCoreApplication::translate("MainWindow", "y", nullptr));
	tab_widget->setTabText(tab_widget->indexOf(tab_properties), QCoreApplication::translate("MainWindow", "Element properties", nullptr));
	b_obstacle->setText(QCoreApplication::translate("MainWindow", "Obstacle", nullptr));
	b_vehicle->setText(QCoreApplication::translate("MainWindow", "Vehicle", nullptr));
	tab_widget->setTabText(tab_widget->indexOf(tab_4), QCoreApplication::translate("MainWindow", "Add element", nullptr));
	menuopen->setTitle(QCoreApplication::translate("MainWindow", "Simulation", nullptr));
} // retranslateUi
