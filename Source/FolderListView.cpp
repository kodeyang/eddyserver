#include "FolderListView.h"

#include <QtWidgets/QScrollBar>


FolderListView::FolderListView(QWidget *parent)
	: QListWidget(parent)
{
	addScrollBarWidget(new QScrollBar(), Qt::AlignRight);
}

FolderListView::~FolderListView()
{

}