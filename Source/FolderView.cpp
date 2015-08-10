#include "FolderView.h"

#include <QtWidgets/QScrollBar>


FolderView::FolderView(QWidget *parent)
	: QListWidget(parent)
{
	refreshFolders(nullptr);
	addScrollBarWidget(new QScrollBar(), Qt::AlignRight);
}

FolderView::~FolderView()
{

}

void FolderView::refreshFolders(DataSource *data_source)
{
	for (int i = 0; i < 10; ++i)
	{
		QListWidgetItem *item = new QListWidgetItem(QIcon(":/images/folder.png"), "dadasda", this);
		item->setFlags(Qt::ItemIsEnabled | Qt::ItemIsEditable);
		addItem(item);
	}
}