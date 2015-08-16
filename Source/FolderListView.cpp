#include "FolderListView.h"

#include <QtWidgets/QScrollBar>
#include "FolderListModel.h"


FolderListView::FolderListView(QSharedPointer<DataSource> data, QWidget *parent)
	: QListView(parent)
{
	setModel(new FolderListModel(data, this));
	addScrollBarWidget(new QScrollBar(), Qt::AlignRight);
}

FolderListView::~FolderListView()
{

}