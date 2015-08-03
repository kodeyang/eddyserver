#pragma once

#include <QtWidgets/QListWidget>

class FolderList : public QListWidget
{
	Q_OBJECT

public:
	explicit FolderList(QWidget *parent = 0);
	~FolderList();
};