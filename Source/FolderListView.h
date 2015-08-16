#pragma once

#include <QtWidgets/QListWidget>


class FolderListView : public QListWidget
{
	Q_OBJECT

public:
	explicit FolderListView(QWidget *parent = 0);
	~FolderListView();
};