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
	for (auto &item_name : data_source->takeCategorys())
	{
		QListWidgetItem *item = new QListWidgetItem(QIcon(":/images/folder.png"), item_name, this);
		item->setFlags(Qt::ItemIsEnabled | Qt::ItemIsEditable);
		addItem(item);
	}
}