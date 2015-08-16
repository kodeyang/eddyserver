#include "DataSource.h"

#include <QtGlobal>
#include <QtAlgorithms>

#include "rapidjson/writer.h" 
#include "rapidjson/document.h"
#include "rapidjson/stringbuffer.h" 


rapidjson::Value ToJsonString(const QString &text, rapidjson::Document::AllocatorType &allocator)
{
	rapidjson::Value json_string;
	json_string.SetString(text.toStdString().c_str(), allocator);
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
	rapidjson::Document::AllocatorType &allocator = doc.GetAllocator();
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

			json_object.AddMember("title", ToJsonString(pw_data.title, allocator), allocator);
			json_object.AddMember("user_name", ToJsonString(pw_data.user_name, allocator), allocator);
			json_object.AddMember("pass_word", ToJsonString(pw_data.pass_word, allocator), allocator);
			json_object.AddMember("url", ToJsonString(pw_data.url, allocator), allocator);
			json_object.AddMember("notes", ToJsonString(pw_data.notes, allocator), allocator);

			json_array.PushBack(json_object, allocator);
		}

		doc.AddMember(ToJsonString(category_name, allocator), json_array, allocator);
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
}

QVector<QString> DataSource::categorys() const
{
	return category_order_;
}

bool DataSource::addCategory(const QString &name)
{
	auto itr = all_records_.find(name);
	if (itr != all_records_.end())
	{
		return false;
	}
	else
	{
		category_order_.push_back(name);
		all_records_.insert(name, std::move(QVector<PWData>()));
		return true;
	}
}

bool DataSource::deleteCategory(size_t index)
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

		return true;
	}
	else
	{
		return false;
	}
}

bool DataSource::renameCategory(size_t index, const QString &new_name)
{
	if (index < category_order_.size())
	{
		QString &category_name = category_order_[index];

		if (category_name == new_name)
		{
			return false;
		}

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

			return true;
		}
	}
	return false;
}