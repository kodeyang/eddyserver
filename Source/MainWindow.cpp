#include "MainWindow.h"

#include <QFile>
#include <QtWidgets/QMenuBar>
#include <QtWidgets/QToolBar>
#include <QtWidgets/QSplitter>
#include <QtWidgets/QFileDialog>
#include <QtWidgets/QMessageBox>

#include "DocTableView.h"
#include "FolderListView.h"


MainWindow::MainWindow(QWidget *parent, Qt::WindowFlags flags)
	: QMainWindow(parent, flags)
	, new_action_(nullptr)
	, open_action_(nullptr)
	, save_action_(nullptr)
	, data_source_(new DataSource())
{
	createActions();

	createFileMenu();

	auto splitter = new QSplitter(this);
	setCentralWidget(splitter);

	FolderListView *folderView = new FolderListView(data_source_, this);
	splitter->addWidget(folderView);

	auto docView = new DocTableView(this);
	splitter->addWidget(docView);

	splitter->setStretchFactor(0, 20);
	splitter->setStretchFactor(1, 80);

	statusBar();
	setMinimumSize(QSize(840, 460));
}

MainWindow::~MainWindow()
{

}

void MainWindow::createActions()
{
	new_action_ = new QAction(QIcon(":/images/folder_new.png"), tr("&New"), this);
	new_action_->setShortcut(QKeySequence::New);

	open_action_ = new QAction(QIcon(":/images/folder_open.png"), tr("&Open"), this);
	open_action_->setShortcut(QKeySequence::Open);
	QObject::connect(open_action_, SIGNAL(triggered()), this, SLOT(openFile()));

	save_action_ = new QAction(QIcon(":/images/folder_open.png"), tr("&Save"), this);
	save_action_->setShortcut(QKeySequence::Save);
	QObject::connect(save_action_, SIGNAL(triggered()), this, SLOT(saveFile()));
}

void MainWindow::createFileMenu()
{
	auto file_menu_ = menuBar()->addMenu(tr("&File"));
	file_menu_->addAction(new_action_);
	file_menu_->addAction(open_action_);
	file_menu_->addAction(save_action_);
}

void MainWindow::openFile()
{
	current_file_ = QFileDialog::getOpenFileName(this, tr("Open"), ".", tr("Password files (*.pw)"));
	if (!current_file_.isEmpty())
	{
		QFile file(current_file_);
		file.open(QIODevice::OpenModeFlag::ReadOnly);
		data_source_->importData(file.readAll());
	}
}

void MainWindow::saveFile()
{
	if (!current_file_.isEmpty())
	{
		QFile file(current_file_);
		file.open(QIODevice::OpenModeFlag::WriteOnly);
		file.write(data_source_->exportData());
	}
}