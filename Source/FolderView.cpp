#include "FolderView.h"

#include <QtWidgets/QScrollBar>


FolderView::FolderView(QWidget *parent)
	: QListWidget(parent)
{
	addScrollBarWidget(new QScrollBar(), Qt::AlignRight);
}

FolderView::~FolderView()
{

}