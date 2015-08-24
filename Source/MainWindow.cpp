#include "MainWindow.h"

#include <QFile>
#include <QtWidgets/QMenuBar>
#include <QtWidgets/QToolBar>
#include <QtWidgets/QSplitter>
#include <QtWidgets/QFileDialog>

#include "CategoryView.h"
#include "DocumentTableView.h"


MainWindow::MainWindow(QWidget *parent, Qt::WindowFlags flags)
	: QMainWindow(parent, flags)
	, database_(new DataSource())
	, document_view_(new DocumentTableView(this))
	, category_view_(new CategoryView(database_, this))
{
	setupFileActions();
	setMinimumSize(QSize(640, 480));

	QSplitter *splitter = new QSplitter(Qt::Horizontal, this);
	splitter->addWidget(category_view_);
	splitter->addWidget(document_view_);
	splitter->setStretchFactor(0, 30);
	splitter->setStretchFactor(1, 70);
	setCentralWidget(splitter);

	statusBar();

	connect(database_.data(), &DataSource::categoryCreated, category_view_, &CategoryView::categoryCreated);
	connect(database_.data(), &DataSource::categoryDeleted, category_view_, &CategoryView::categoryDeleted);
	connect(database_.data(), &DataSource::categoryModified, category_view_, &CategoryView::categoryModified);
}

MainWindow::~MainWindow()
{

}

void MainWindow::setupFileActions()
{
	QToolBar *tb = new QToolBar(this);
	tb->setWindowTitle(tr("File Actions"));
	addToolBar(tb);

	QMenu *menu = new QMenu(tr("&File"), this);
	menuBar()->addMenu(menu);

	QAction *new_action = new QAction(QIcon(":/images/file-new.png"), tr("&New"), this);
	new_action->setShortcut(QKeySequence::New);
	menu->addAction(new_action);
	tb->addAction(new_action);
	QObject::connect(new_action, &QAction::triggered, this, &MainWindow::newFile);

	menu->addSeparator();

	QAction *open_action = new QAction(QIcon(":/images/file-open.png"), tr("&Open"), this);
	open_action->setShortcut(QKeySequence::Open);
	menu->addAction(open_action);
	tb->addAction(open_action);
	QObject::connect(open_action, &QAction::triggered, this, &MainWindow::openFile);

	menu->addSeparator();

	QAction *save_action = new QAction(QIcon(":/images/file-save.png"), tr("&Save"), this);
	save_action->setShortcut(QKeySequence::Save);
	menu->addAction(save_action);
	tb->addAction(save_action);
	QObject::connect(save_action, &QAction::triggered, this, &MainWindow::saveFile);
}

void MainWindow::newFile()
{

}

void MainWindow::openFile()
{
	curr_opened_file_ = QFileDialog::getOpenFileName(this, tr("Open"), ".", tr("Password files (*.pw)"));
	if (!curr_opened_file_.isEmpty())
	{
		QFile file(curr_opened_file_);
		file.open(QIODevice::OpenModeFlag::ReadOnly);
		database_->importData(file.readAll());
	}
}

void MainWindow::saveFile()
{
	if (!curr_opened_file_.isEmpty())
	{
		QFile file(curr_opened_file_);
		file.open(QIODevice::ReadWrite);
		file.write(database_->exportData());
	}
}