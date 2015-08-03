#include "FolderList.h"

#include <QtWidgets/QScrollBar>


FolderList::FolderList(QWidget *parent)
	: QListWidget(parent)
{
	addScrollBarWidget(new QScrollBar(), Qt::AlignRight);
}

FolderList::~FolderList()
{

}