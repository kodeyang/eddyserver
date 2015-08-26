#include "CategoryView.h"

#include <QtWidgets/QMenu>
#include <QtWidgets/QMessageBox>
#include <QtWidgets/QInputDialog>


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

	QAction *new_category = new QAction(QStringLiteral("新建分类"), this);
	blank_right_menu_->addAction(new_category);
	connect(new_category, &QAction::triggered, this, &CategoryView::newCategory);

	QAction *new_document = new QAction(QStringLiteral("新建文档"), this);
	right_menu_->addAction(new_document);

	QAction *del_category = new QAction(QStringLiteral("删除分类"), this);
	right_menu_->addAction(del_category);
	connect(del_category, &QAction::triggered, this, &CategoryView::deleteCategory);

	QAction *rename_category = new QAction(QStringLiteral("重命名分类"), this);
	right_menu_->addAction(rename_category);
	connect(rename_category, &QAction::triggered, this, &CategoryView::renameCategory);
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
		disconnect(this, &QListWidget::itemChanged, this, &CategoryView::itemModified);
		item->setText(database_->category(index));
		QMessageBox::information(NULL, QStringLiteral("提示"), QStringLiteral("已有同名分类存在，重命名失败！"), QMessageBox::Yes);
		connect(this, &QListWidget::itemChanged, this, &CategoryView::itemModified);
	}
}

void CategoryView::newCategory()
{
	bool ok = false;
	QString text = QInputDialog::getText(NULL, QStringLiteral("新建分类"), QStringLiteral("请输入分类名称："), QLineEdit::Normal, NULL, &ok);
	if (ok && !text.isEmpty())
	{
		if (!database_->hasCategory(text))
		{
			database_->createCategory(text);
		}
		else
		{
			QMessageBox::information(NULL, QStringLiteral("提示"), QStringLiteral("已有同名分类存在，新建分类失败！"), QMessageBox::Yes);
		}
	}
}

void CategoryView::deleteCategory()
{
	if (QListWidgetItem *item_ptr = currentItem())
	{	
		if (QMessageBox::Yes ==
			QMessageBox::information(NULL, QStringLiteral("警告"), QStringLiteral("此分类下所有文档将被删除，是否继续？"), QMessageBox::Yes | QMessageBox::No))
		{
			int index = row(item_ptr);
			database_->deleteCategory(index);
		}
	}
}

void CategoryView::renameCategory()
{
	if (QListWidgetItem *item_ptr = currentItem())
	{
		editItem(item_ptr);
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
	item_ptr->setIcon(QIcon(":/images/file-open.png"));
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