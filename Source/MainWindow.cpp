#include "MainWindow.h"

#include <QtWidgets/QMenuBar>
#include <QtWidgets/QToolBar>
#include <QtWidgets/QSplitter>

#include "DocList.h"
#include "FolderList.h"


MainWindow::MainWindow(QWidget *parent, Qt::WindowFlags flags)
	: QMainWindow(parent, flags)
	, new_action_(nullptr)
	, open_action_(nullptr)
{
	createActions();

	createFileMenu();

	auto splitter = new QSplitter(this);
	setCentralWidget(splitter);

	auto folder_list = new FolderList(this);
	splitter->addWidget(folder_list);

	auto doc_list = new DocList(this);
	splitter->addWidget(doc_list);

	splitter->setStretchFactor(0, 2);
	splitter->setStretchFactor(1, 8);

	statusBar();
}

MainWindow::~MainWindow()
{

}

void MainWindow::createActions()
{
	new_action_ = new QAction(QIcon(":/images/doc_new.png"), tr("&New"), this);
	new_action_->setShortcut(QKeySequence::New);

	open_action_ = new QAction(QIcon(":/images/folder_open.png"), tr("&Open"), this);
	open_action_->setShortcut(QKeySequence::Open);
}

void MainWindow::createFileMenu()
{
	auto file_menu_ = menuBar()->addMenu(tr("&File"));
	file_menu_->addAction(new_action_);
	file_menu_->addAction(open_action_);
}