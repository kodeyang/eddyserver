﻿#include "MainWindow.h"

#include <QFile>
#include <QtWidgets/QMenuBar>
#include <QtWidgets/QToolBar>
#include <QtWidgets/QSplitter>
#include <QtWidgets/QFileDialog>
#include <QtWidgets/QMessageBox>

#include "DoccView.h"
#include "FolderView.h"


MainWindow::MainWindow(QWidget *parent, Qt::WindowFlags flags)
	: QMainWindow(parent, flags)
	, new_action_(nullptr)
	, open_action_(nullptr)
	, data_source_(new DataSource())
{
	createActions();

	createFileMenu();

	auto splitter = new QSplitter(this);
	setCentralWidget(splitter);

	auto folder_list = new FolderView(this);
	splitter->addWidget(folder_list);

	auto doc_list = new DoccView(this);
	splitter->addWidget(doc_list);

	splitter->setStretchFactor(0, 20);
	splitter->setStretchFactor(1, 80);

	statusBar();
	setMinimumSize(QSize(840, 460));

	QObject::connect(data_source_.data(), &DataSource::message, this, &MainWindow::popupMessage);
	QObject::connect(data_source_.data(), &DataSource::refresh, folder_list, &FolderView::refreshFolders);
	QObject::connect(folder_list, &FolderView::renameFolder, data_source_.data(), &DataSource::renameCategory);
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
}

void MainWindow::createFileMenu()
{
	auto file_menu_ = menuBar()->addMenu(tr("&File"));
	file_menu_->addAction(new_action_);
	file_menu_->addAction(open_action_);
}

void MainWindow::openFile()
{
	QString file_name = QFileDialog::getOpenFileName(this, tr("Open"), ".", tr("Password files (*.pw)"));
	if (!file_name.isEmpty())
	{
		QFile file(file_name);
		file.open(QIODevice::OpenModeFlag::ReadOnly);
		data_source_->importData(file.readAll());
	}
}

void MainWindow::popupMessage(DataSource::MessageCode code, const QString &details)
{
	QMessageBox message_box(this);
	message_box.setWindowTitle(tr("Tips"));
	message_box.addButton(tr("OK"), QMessageBox::ActionRole);
	message_box.setText(details);
	message_box.exec();
}