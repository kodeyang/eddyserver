#pragma once

#include <QtWidgets/QListWidget>


class FolderView : public QListWidget
{
	Q_OBJECT

public:
	explicit FolderView(QWidget *parent = 0);
	~FolderView();
};