#pragma once

#include <QtWidgets/QMainWindow>
#include "DataSource.h"

class CategoryView;
class DocumentTableView;

class MainWindow final : public QMainWindow
{
	Q_OBJECT

public:
	MainWindow(QWidget *parent = nullptr, Qt::WindowFlags flags = 0);
	
	~MainWindow();

private:
	void setupFileActions();

private Q_SLOTS:
	void newFile();

	void openFile();

	void saveFile();

private:
	database_ptr		database_;
	CategoryView*		category_view_;
	DocumentTableView*	document_view_;
	QString				curr_opened_file_;
};