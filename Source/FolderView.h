#pragma once

#include <QtWidgets/QListWidget>

class DataSource;

class FolderView : public QListWidget
{
	Q_OBJECT

public:
	explicit FolderView(QWidget *parent = 0);
	~FolderView();

public Q_SLOTS:
	void refreshFolders(DataSource *data_source);

Q_SIGNALS:
	void renameFolder(const QString &name, const QString &new_name);
};