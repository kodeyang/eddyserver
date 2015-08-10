#include "DataSource.h"

#include <QtGlobal>
#include <QtAlgorithms>


DataSource::DataSource()
{

}

DataSource::~DataSource()
{

}

{
	rapidjson::Document doc;
	doc.Parse<0>(bytes.data());

	if (doc.HasParseError())
	{
		qDebug() << "has parse error.";
		return;
	}

	for (auto itr = doc.MemberBegin(); itr != doc.MemberEnd(); ++itr)
	{
		if (itr->name.IsString() && itr->value.IsArray())
		{
			const rapidjson::Value &json_array = itr->value;
			for (size_t idx = 0; idx < json_array.Size(); ++idx)
			{
				if (json_array[idx].IsObject())
				{
					const rapidjson::Value &json_object = json_array[idx];
					if (json_object.HasMember("title")
						&& json_object.HasMember("user_name")
						&& json_object.HasMember("pass_word")
						&& json_object.HasMember("url")
						&& json_object.HasMember("notes")
						&& json_object["title"].IsString()
						&& json_object["user_name"].IsString()
						&& json_object["pass_word"].IsString()
						&& json_object["url"].IsString()
						&& json_object["notes"].IsString()
						)
					{
						PWData data;
						data.title = json_object["title"].GetString();
						data.user_name = json_object["user_name"].GetString();
						data.pass_word = json_object["pass_word"].GetString();
						data.url = json_object["url"].GetString();
						data.notes = json_object["notes"].GetString();
						all_record_[itr->name.GetString()].push_back(std::move(data));
					}
				}
			}
		}
	}
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