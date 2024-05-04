#include "interface.hpp"

interface::interface(/* args */)
{
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
	horizontalLayoutWidget = new QWidget(centralwidget);
	horizontalLayoutWidget->setObjectName(QString::fromUtf8("horizontalLayoutWidget"));
	horizontalLayoutWidget->setGeometry(QRect(0, 0, 1327, 722));
	horizontalLayout = new QHBoxLayout(horizontalLayoutWidget);
	horizontalLayout->setObjectName(QString::fromUtf8("horizontalLayout"));
	horizontalLayout->setContentsMargins(0, 0, 0, 0);
	verticalLayout_2 = new QVBoxLayout();
	verticalLayout_2->setObjectName(QString::fromUtf8("verticalLayout_2"));
	groupBox = new QGroupBox(horizontalLayoutWidget);
	groupBox->setObjectName(QString::fromUtf8("groupBox"));
	QSizePolicy sizePolicy(QSizePolicy::Preferred, QSizePolicy::Preferred);
	sizePolicy.setHorizontalStretch(0);
	sizePolicy.setVerticalStretch(1);
	sizePolicy.setHeightForWidth(groupBox->sizePolicy().hasHeightForWidth());
	groupBox->setSizePolicy(sizePolicy);
	groupBox->setMinimumSize(QSize(400, 0));
	groupBox->setMaximumSize(QSize(16777215, 300));
	groupBox->setSizeIncrement(QSize(1, 1));
	items = new QTableWidget(groupBox);
	items->setObjectName(QString::fromUtf8("items"));
	items->setGeometry(QRect(0, 20, 400, 220));
	horizontalLayoutWidget_2 = new QWidget(groupBox);
	horizontalLayoutWidget_2->setObjectName(QString::fromUtf8("horizontalLayoutWidget_2"));
	horizontalLayoutWidget_2->setGeometry(QRect(0, 239, 401, 61));
	horizontalLayout_2 = new QHBoxLayout(horizontalLayoutWidget_2);
	horizontalLayout_2->setObjectName(QString::fromUtf8("horizontalLayout_2"));
	horizontalLayout_2->setSizeConstraint(QLayout::SetMaximumSize);
	horizontalLayout_2->setContentsMargins(0, 0, 0, 0);
	b_remove = new QCommandLinkButton(horizontalLayoutWidget_2);
	b_remove->setObjectName(QString::fromUtf8("b_remove"));
	b_remove->setMaximumSize(QSize(150, 16777215));
	b_remove->setSizeIncrement(QSize(0, 0));

	horizontalLayout_2->addWidget(b_remove);

	b_reset = new QCommandLinkButton(horizontalLayoutWidget_2);
	b_reset->setObjectName(QString::fromUtf8("b_reset"));
	b_reset->setMaximumSize(QSize(80, 16777215));
	b_reset->setSizeIncrement(QSize(0, 0));

	horizontalLayout_2->addWidget(b_reset);

	b_launch = new QCommandLinkButton(horizontalLayoutWidget_2);
	b_launch->setObjectName(QString::fromUtf8("b_launch"));
	b_launch->setMaximumSize(QSize(80, 16777215));
	b_launch->setSizeIncrement(QSize(0, 0));

	horizontalLayout_2->addWidget(b_launch);

	verticalLayout_2->addWidget(groupBox);

	tabWidget = new QTabWidget(horizontalLayoutWidget);
	tabWidget->setObjectName(QString::fromUtf8("tabWidget"));
	tab_properties = new QWidget();
	tab_properties->setObjectName(QString::fromUtf8("tab_properties"));
	formLayoutWidget = new QWidget(tab_properties);
	formLayoutWidget->setObjectName(QString::fromUtf8("formLayoutWidget"));
	formLayoutWidget->setGeometry(QRect(-1, -1, 401, 131));
	formLayout = new QFormLayout(formLayoutWidget);
	formLayout->setObjectName(QString::fromUtf8("formLayout"));
	formLayout->setLabelAlignment(Qt::AlignCenter);
	formLayout->setContentsMargins(18, 0, 0, 0);
	label = new QLabel(formLayoutWidget);
	label->setObjectName(QString::fromUtf8("label"));
	QSizePolicy sizePolicy1(QSizePolicy::Preferred, QSizePolicy::Preferred);
	sizePolicy1.setHorizontalStretch(0);
	sizePolicy1.setVerticalStretch(0);
	sizePolicy1.setHeightForWidth(label->sizePolicy().hasHeightForWidth());
	label->setSizePolicy(sizePolicy1);
	label->setMinimumSize(QSize(100, 0));
	label->setAlignment(Qt::AlignCenter);
	label->setMargin(1);

	formLayout->setWidget(0, QFormLayout::LabelRole, label);

	in_x = new QLineEdit(formLayoutWidget);
	in_x->setObjectName(QString::fromUtf8("in_x"));
	in_x->setMinimumSize(QSize(0, 0));
	in_x->setMaximumSize(QSize(200, 16777215));

	formLayout->setWidget(0, QFormLayout::FieldRole, in_x);

	in_y = new QLineEdit(formLayoutWidget);
	in_y->setObjectName(QString::fromUtf8("in_y"));
	in_y->setMaximumSize(QSize(200, 16777215));
	in_y->setSizeIncrement(QSize(0, 0));

	formLayout->setWidget(1, QFormLayout::FieldRole, in_y);

	label_3 = new QLabel(formLayoutWidget);
	label_3->setObjectName(QString::fromUtf8("label_3"));
	label_3->setMinimumSize(QSize(100, 0));
	label_3->setAlignment(Qt::AlignCenter);

	formLayout->setWidget(2, QFormLayout::LabelRole, label_3);

	in_rotation = new QLineEdit(formLayoutWidget);
	in_rotation->setObjectName(QString::fromUtf8("in_rotation"));
	in_rotation->setMaximumSize(QSize(200, 16777215));

	formLayout->setWidget(2, QFormLayout::FieldRole, in_rotation);

	label_4 = new QLabel(formLayoutWidget);
	label_4->setObjectName(QString::fromUtf8("label_4"));

	formLayout->setWidget(3, QFormLayout::LabelRole, label_4);

	in_animator = new QComboBox(formLayoutWidget);
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

	formLayout->setWidget(3, QFormLayout::FieldRole, in_animator);

	label_2 = new QLabel(formLayoutWidget);
	label_2->setObjectName(QString::fromUtf8("label_2"));
	QSizePolicy sizePolicy3(QSizePolicy::Fixed, QSizePolicy::Fixed);
	sizePolicy3.setHorizontalStretch(0);
	sizePolicy3.setVerticalStretch(1);
	sizePolicy3.setHeightForWidth(label_2->sizePolicy().hasHeightForWidth());
	label_2->setSizePolicy(sizePolicy3);
	label_2->setMinimumSize(QSize(100, 0));
	label_2->setAlignment(Qt::AlignCenter);

	formLayout->setWidget(1, QFormLayout::LabelRole, label_2);

	tabWidget->addTab(tab_properties, QString());
	tab_4 = new QWidget();
	tab_4->setObjectName(QString::fromUtf8("tab_4"));
	gridLayoutWidget = new QWidget(tab_4);
	gridLayoutWidget->setObjectName(QString::fromUtf8("gridLayoutWidget"));
	gridLayoutWidget->setGeometry(QRect(10, 9, 381, 71));
	gridLayout_4 = new QGridLayout(gridLayoutWidget);
	gridLayout_4->setObjectName(QString::fromUtf8("gridLayout_4"));
	gridLayout_4->setSizeConstraint(QLayout::SetMinimumSize);
	gridLayout_4->setContentsMargins(0, 0, 0, 0);
	b_obstacle = new QToolButton(gridLayoutWidget);
	b_obstacle->setObjectName(QString::fromUtf8("b_obstacle"));
	b_obstacle->setMinimumSize(QSize(50, 50));

	gridLayout_4->addWidget(b_obstacle, 0, 1, 1, 1);

	b_vehicle = new QToolButton(gridLayoutWidget);
	b_vehicle->setObjectName(QString::fromUtf8("b_vehicle"));
	b_vehicle->setMinimumSize(QSize(50, 50));

	gridLayout_4->addWidget(b_vehicle, 0, 0, 1, 1);

	tabWidget->addTab(tab_4, QString());

	verticalLayout_2->addWidget(tabWidget);

	horizontalLayout->addLayout(verticalLayout_2);

	openGLWidget = new QOpenGLWidget(horizontalLayoutWidget);
	openGLWidget->setObjectName(QString::fromUtf8("openGLWidget"));
	QSizePolicy sizePolicy4(QSizePolicy::Expanding, QSizePolicy::Expanding);
	sizePolicy4.setHorizontalStretch(1);
	sizePolicy4.setVerticalStretch(1);
	sizePolicy4.setHeightForWidth(openGLWidget->sizePolicy().hasHeightForWidth());
	openGLWidget->setSizePolicy(sizePolicy4);
	openGLWidget->setMinimumSize(QSize(824, 720));
	openGLWidget->setSizeIncrement(QSize(1, 1));

	horizontalLayout->addWidget(openGLWidget);

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

	tabWidget->setCurrentIndex(0);

	QMetaObject::connectSlotsByName(MainWindow);
} // setupUi

void interface::retranslateUi(QMainWindow *MainWindow)
{
	MainWindow->setWindowTitle(QCoreApplication::translate("MainWindow", "MainWindow", nullptr));
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
	groupBox->setTitle(QCoreApplication::translate("MainWindow", "Map elements", nullptr));
	b_remove->setText(QCoreApplication::translate("MainWindow", "Remove element", nullptr));
#if QT_CONFIG(shortcut)
	b_remove->setShortcut(QCoreApplication::translate("MainWindow", "Del", nullptr));
#endif // QT_CONFIG(shortcut)
	b_reset->setText(QCoreApplication::translate("MainWindow", "Reset", nullptr));
	b_launch->setText(QCoreApplication::translate("MainWindow", "Launch", nullptr));
#if QT_CONFIG(shortcut)
	b_launch->setShortcut(QCoreApplication::translate("MainWindow", "F5", nullptr));
#endif // QT_CONFIG(shortcut)
	label->setText(QCoreApplication::translate("MainWindow", "x", nullptr));
	label_3->setText(QCoreApplication::translate("MainWindow", "rotation [\302\260]", nullptr));
	label_4->setText(QCoreApplication::translate("MainWindow", "Animator", nullptr));
	in_animator->setItemText(0, QCoreApplication::translate("MainWindow", "User", nullptr));
	in_animator->setItemText(1, QCoreApplication::translate("MainWindow", "AI", nullptr));

	label_2->setText(QCoreApplication::translate("MainWindow", "y", nullptr));
	tabWidget->setTabText(tabWidget->indexOf(tab_properties), QCoreApplication::translate("MainWindow", "Element properties", nullptr));
	b_obstacle->setText(QCoreApplication::translate("MainWindow", "Obstacle", nullptr));
	b_vehicle->setText(QCoreApplication::translate("MainWindow", "Vehicle", nullptr));
	tabWidget->setTabText(tabWidget->indexOf(tab_4), QCoreApplication::translate("MainWindow", "Add element", nullptr));
	menuopen->setTitle(QCoreApplication::translate("MainWindow", "Simulation", nullptr));
} // retranslateUi
