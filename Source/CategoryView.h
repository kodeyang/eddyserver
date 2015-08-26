#include <QtWidgets/QListWidget>
#include "DataSource.h"


class CategoryView : public QListWidget
{
public:
	explicit CategoryView(database_ptr db, QWidget *parent = 0);

	~CategoryView();

public Q_SLOTS:
	void rightClickMenu(const QPoint &pos);

	void categoryDeleted(const size_t index);

	void categoryCreated(const QString &name);

	void categoryModified(const size_t index, const QString &new_name);

private Q_SLOTS:
	void itemModified(QListWidgetItem *item);

private:
	void setupMenus();

	void newCategory();

	void deleteCategory();

	void renameCategory();

private:
	QMenu*			right_menu_;
	QMenu*			blank_right_menu_;
	database_ptr	database_;
};