#include "FolderView.h"

#include <QtWidgets/QScrollBar>


FolderView::FolderView(QWidget *parent)
	: QListWidget(parent)
{
	addScrollBarWidget(new QScrollBar(), Qt::AlignRight);
	refreshFolders(nullptr);
}

FolderView::~FolderView()
{

}

void FolderView::refreshFolders(DataSource *data_source)
{
	for (int i = 0; i < 10; ++i)
	{
		QListWidgetItem *item = new QListWidgetItem(QIcon(":/images/folder.png"), "dadasda", this);
		addItem(item);
	}
}