#include "DataSource.h"

#include <QtGlobal>
#include <QtAlgorithms>

#include "rapidjson/writer.h" 
#include "rapidjson/document.h"
#include "rapidjson/stringbuffer.h" 

#include <QDebug>


rapidjson::Value QStringToJString(const QString &text)
{
	rapidjson::Value json_string;
	std::string str = text.toLocal8Bit();
	json_string.SetString(str.data(), str.size());
	return json_string;
}

DataSource::DataSource()
{

}

DataSource::~DataSource()
{

}

QByteArray DataSource::exportData() const
{
	rapidjson::Document doc;
	doc.SetObject();

	for (auto &category_name : category_order_)
	{
		auto category_itr = all_records_.find(category_name);
		Q_ASSERT(category_itr != all_records_.end());

		rapidjson::Value json_array;
		json_array.SetArray();
		for (auto &pw_data : *category_itr)
		{
			rapidjson::Value json_object;
			json_object.SetObject();

			json_object.AddMember("title", QStringToJString(pw_data.title), doc.GetAllocator());
			json_object.AddMember("user_name", QStringToJString(pw_data.user_name), doc.GetAllocator());
			json_object.AddMember("pass_word", QStringToJString(pw_data.pass_word), doc.GetAllocator());
			json_object.AddMember("url", QStringToJString(pw_data.url), doc.GetAllocator());
			json_object.AddMember("notes", QStringToJString(pw_data.notes), doc.GetAllocator());

			json_array.PushBack(json_object, doc.GetAllocator());
		}

		doc.AddMember(QStringToJString(category_name), json_array, doc.GetAllocator());
	}

	rapidjson::StringBuffer buffer;
	rapidjson::Writer<rapidjson::StringBuffer> writer(buffer);
	doc.Accept(writer);

	return QByteArray(buffer.GetString(), buffer.GetSize());
}

void DataSource::importData(const QByteArray &bytes)
{
	all_records_.clear();
	category_order_.clear();

	rapidjson::Document doc;
	doc.Parse<0>(bytes.data());

	if (!doc.HasParseError())
	{
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
							all_records_[itr->name.GetString()].push_back(std::move(data));
						}
					}
				}
				category_order_.push_back(itr->name.GetString());
			}
		}
	}

	emit refresh(this);
}

QVector<QString> DataSource::getCategorys() const
{
	return category_order_;
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

void DataSource::deleteCategory(size_t index)
{
	if (index < category_order_.size())
	{
		QString &category_name = category_order_[index];
		auto category_itr = all_records_.find(category_name);
		Q_ASSERT(category_itr != all_records_.end());

		all_records_.erase(category_itr);

		auto order_itr = qFind(category_order_.begin(), category_order_.end(), category_name);
		Q_ASSERT(order_itr != category_order_.end());
		category_order_.erase(order_itr);

		emit refresh(this);
	}
	else
	{
		emit refresh(this);
		emit message(CATEGORY_NOT_EXISTS, tr("category does not exist failed to delete category"));
	}
}

void DataSource::renameCategory(size_t index, const QString &new_name)
{
	if (index < category_order_.size())
	{
		QString &category_name = category_order_[index];

		if (category_name == new_name) return;

		auto category_itr = all_records_.find(category_name);
		Q_ASSERT(category_itr != all_records_.end());

		if (all_records_.find(new_name) == all_records_.end())
		{
			QVector<PWData> records(std::move(*category_itr));
			all_records_.erase(category_itr);
			all_records_.insert(new_name, std::move(records));

			auto order_itr = qFind(category_order_.begin(), category_order_.end(), category_name);
			Q_ASSERT(order_itr != category_order_.end());
			*order_itr = new_name;

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