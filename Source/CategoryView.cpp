#include "CategoryView.h"


CategoryView::CategoryView(database_ptr db, QWidget *parent)
	: QListWidget(parent)
	, database_(db)
{

}

CategoryView::~CategoryView()
{

}

void CategoryView::categoryDeleted(const size_t index)
{
	if (QListWidgetItem *item_ptr = takeItem(index))
	{
		removeItemWidget(item_ptr);
		delete item_ptr;
	}
}

void CategoryView::categoryCreated(const QString &name)
{
	QListWidgetItem *item_ptr = new QListWidgetItem(name);
	item_ptr->setFlags(Qt::ItemIsSelectable
					   | Qt::ItemIsUserCheckable
					   | Qt::ItemIsEnabled
					   | Qt::ItemIsDragEnabled
					   | Qt::ItemIsEditable);
	addItem(item_ptr);
}

void CategoryView::categoryModified(const size_t index, const QString &new_name)
{
	if (QListWidgetItem *item_ptr = item(index))
	{
		item_ptr->setText(new_name);
	}
}