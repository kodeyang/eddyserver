#pragma once

#include <QtWidgets/QMainWindow>

class MainWindow final : public QMainWindow
{
	Q_OBJECT

public:
	MainWindow(QWidget *parent = nullptr, Qt::WindowFlags flags = 0);
	
	~MainWindow();

private:
	/**
	 * 创建动作
	 */
	void createActions();

	/**
	 * 创建菜单
	 */
	void createMenus();

private:
	// 菜单项
	QMenu* file_menu_;
	QMenu* edit_menu_;
	QMenu* tools_menu_;
	QMenu* options_menu_;
	QMenu* help_menu_;

	// 动作项
	QAction* new_action_;
	QAction* open_action_;
};