#pragma once

#include <QtWidgets/QListView>

class DataSource;
class FolderListModel;

class FolderListView : public QListView
{
	Q_OBJECT

public:
	explicit FolderListView(QSharedPointer<DataSource> data, QWidget *parent = 0);

	~FolderListView();

private:
	FolderListModel* model_;
};