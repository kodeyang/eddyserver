#include "MainWindow.h"

#include <QtWidgets/QMenuBar>

MainWindow::MainWindow(QWidget *parent, Qt::WindowFlags flags)
	: QMainWindow(parent, flags)
	, file_menu_(nullptr)
	, edit_menu_(nullptr)
	, tools_menu_(nullptr)
	, options_menu_(nullptr)
	, help_menu_(nullptr)
	, new_action_(nullptr)
	, open_action_(nullptr)
{
	createActions();
	createMenus();
	statusBar();
	setWindowTitle("PasswordBox");
	setMinimumSize(geometry().width(), geometry().height());
}

MainWindow::~MainWindow()
{

}

// 创建动作
void MainWindow::createActions()
{
	// new action
	new_action_ = new QAction(tr("&New"), this);
	new_action_->setShortcut(QKeySequence::New);

	// open action
	open_action_ = new QAction(tr("&Open"), this);
	open_action_->setShortcut(QKeySequence::Open);
}

// 创建菜单
void MainWindow::createMenus()
{
	// file menu
	file_menu_ = menuBar()->addMenu(tr("&File"));
	file_menu_->addAction(new_action_);
	file_menu_->addAction(open_action_);

	// edit menu
	edit_menu_ = menuBar()->addMenu(tr("&Edit"));

	// tools menu
	tools_menu_ = menuBar()->addMenu(tr("&Tools"));

	// options menu
	options_menu_ = menuBar()->addMenu(tr("&Options"));

	// help menu
	help_menu_ = menuBar()->addMenu(tr("&Help"));
}