#include "FolderView.h"

#include <QtWidgets/QScrollBar>

#include "DataSource.h"


FolderView::FolderView(QWidget *parent)
	: QListWidget(parent)
{
	addScrollBarWidget(new QScrollBar(), Qt::AlignRight);
}

FolderView::~FolderView()
{

}

void FolderView::refreshFolders(DataSource *data_source)
{
	QListWidgetItem *item = new QListWidgetItem(QIcon(":/images/folder.png"), "dadasda", this);
	item->setFlags(Qt::ItemIsEnabled | Qt::ItemIsEditable);
	addItem(item);
}