#include "DataSource.h"

#include <QtGlobal>
#include <QtAlgorithms>


DataSource::DataSource()
{

}

DataSource::~DataSource()
{

}

void DataSource::addCategory(const QString &name)
{
	auto itr = all_records_.find(name);
	if (itr != all_records_.end())
	{
		emit refresh(this);
		emit message(CATEGORY_EXISTS, tr("category already exists, add category failed"));
	}
	else
	{
		category_order_.push_back(name);
		all_records_.insert(name, std::move(QVector<PWData>()));
		emit refresh(this);
	}
}

void DataSource::deleteCategory(const QString &name)
{
	auto itr = all_records_.find(name);
	if (itr != all_records_.end())
	{
		
		all_records_.erase(itr);
		emit refresh(this);
	}
	else
	{
		auto result = qFind(category_order_.begin(), category_order_.end(), name);
		Q_ASSERT(result != category_order_.end());
		category_order_.erase(result);

		emit refresh(this);
		emit message(CATEGORY_NOT_EXISTS, tr("category does not exist failed to delete the category"));
	}
}

void DataSource::changeCategoryName(const QString &name, const QString &new_name)
{
	auto itr = all_records_.find(name);
	if (itr != all_records_.end())
	{
		if (all_records_.find(new_name) == all_records_.end())
		{
			QVector<PWData> records(std::move(*itr));
			all_records_.erase(itr);
			all_records_.insert(new_name, std::move(records));

			auto result = qFind(category_order_.begin(), category_order_.end(), name);
			Q_ASSERT(result != category_order_.end());
			*result = new_name;

			emit refresh(this);
		}
		else
		{
			emit refresh(this);
			emit message(CATEGORY_EXISTS, tr("existing category with the same name, rename category failed"));
		}
	}
	else
	{
		emit refresh(this);
		emit message(CATEGORY_NOT_EXISTS, tr("category does not exist, rename category failed"));
	}
}