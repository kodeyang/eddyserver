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
	int idx = 0;
	auto categorys = data_source->getCategorys();
	const int max_size = categorys.size();

	for (; idx < max_size; ++idx)
	{
		if (idx < count())
		{
			QListWidgetItem *item = takeItem(idx);
			item->setText(categorys[idx]);
			addItem(item);
		}
		else
		{
			QListWidgetItem *item = new QListWidgetItem(QIcon(":/images/folder.png"), categorys[idx], this);
			item->setFlags(Qt::ItemIsEnabled | Qt::ItemIsEditable);
			addItem(item);
		}
	}

	for (; idx < count(); ++idx)
	{
		QListWidgetItem *item = takeItem(idx);
		removeItemWidget(item);
		delete item;
	}
}