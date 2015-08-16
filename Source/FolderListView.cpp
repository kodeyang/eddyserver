#include "FolderListView.h"

#include <QtWidgets/QScrollBar>

#include "FolderListModel.h"


FolderListView::FolderListView(QSharedPointer<DataSource> data, QWidget *parent)
	: QListView(parent)
	, model_(nullptr)
{
	model_ = new FolderListModel(data, this);
	addScrollBarWidget(new QScrollBar(), Qt::AlignRight);
	setModel(model_);
}

FolderListView::~FolderListView()
{

}