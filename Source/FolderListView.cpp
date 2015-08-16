#include "FolderListView.h"

#include <QtWidgets/QScrollBar>
#include "DataSource.h"


FolderListView::FolderListView(QSharedPointer<DataSource> data, QWidget *parent)
	: QListView(parent)
{
	addScrollBarWidget(new QScrollBar(), Qt::AlignRight);
}

FolderListView::~FolderListView()
{

}