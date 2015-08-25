#include "CategoryView.h"
#include <QtWidgets/QMenu>


CategoryView::CategoryView(database_ptr db, QWidget *parent)
	: QListWidget(parent)
	, right_menu_(nullptr)
	, blank_right_menu_(nullptr)
	, database_(db)
{
	setupMenus();
	setContextMenuPolicy(Qt::CustomContextMenu);
	connect(this, &QListWidget::itemChanged, this, &CategoryView::itemModified);
	connect(this, &QWidget::customContextMenuRequested, this, &CategoryView::rightClickMenu);
}

CategoryView::~CategoryView()
{

}

void CategoryView::setupMenus()
{
	right_menu_ = new QMenu(this);
	blank_right_menu_ = new QMenu(this);

	QAction *new_category = new QAction(tr("New Category"), this);
	blank_right_menu_->addAction(new_category);

	QAction *new_document = new QAction(tr("New Document"), this);
	right_menu_->addAction(new_document);

	QAction *del_category = new QAction(tr("Delete Category"), this);
	right_menu_->addAction(del_category);

	QAction *rename_category = new QAction(tr("Rename Category"), this);
	right_menu_->addAction(rename_category);
}

void CategoryView::rightClickMenu(const QPoint &pos)
{
	if (QListWidgetItem *item_ptr = itemAt(pos))
	{
		right_menu_->exec(QCursor::pos());
	}
	else
	{
		blank_right_menu_->exec(QCursor::pos());
	}
}

void CategoryView::itemModified(QListWidgetItem *item)
{
	int index = row(item);
	if (!database_->hasCategory(item->text()))
	{
		database_->modifieCategory(index, item->text());
	}
	else
	{
		item->setText(database_->category(index));
	}
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