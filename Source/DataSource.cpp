#include "DataSource.h"

#include <QJsonArray>
#include <QJsonObject>
#include <QJsonDocument>


void DataSource::clear()
{
	if (!category_order_.empty())
	{
		const size_t category_count = category_order_.size();
		for (size_t c_index = category_count - 1; c_index > 0; --c_index)
		{
			auto itr = all_password_data_.find(category_order_[c_index]);
			const size_t document_count = itr->size();

			for (size_t d_index = document_count - 1; d_index > 0; --d_index)
			{
				itr->pop_back();
				emit documentDeleted(c_index, d_index);
			}

			category_order_.pop_back();
			emit categoryDeleted(c_index);
			all_password_data_.erase(itr);
		}
	}
}

QByteArray DataSource::exportData() const
{
	QJsonObject category;
	QJsonDocument document;
	for (auto &category_name : category_order_)
	{
		QJsonArray json_array;
		auto itr = all_password_data_.find(category_name);
		for (size_t index = 0; index < itr->size(); ++index)
		{
			QJsonObject doc_object;
			const PassWordData &data = itr->at(index);
			doc_object.insert("title", data.title);
			doc_object.insert("user_name", data.user_name);
			doc_object.insert("pass_word", data.pass_word);
			doc_object.insert("url", data.url);
			doc_object.insert("notes", data.notes);
			json_array.push_back(doc_object);
		}
		category.insert(category_name, json_array);
	}
	document.setObject(category);
	return document.toJson();
}

void DataSource::importData(const QByteArray &bytes)
{
	clear();

	QJsonParseError error;
	QJsonDocument document = QJsonDocument::fromJson(bytes, &error);
	if (QJsonParseError::NoError == error.error && document.isObject())
	{
		for (QJsonObject::const_iterator c_itr = document.object().constBegin(); c_itr != document.object().constEnd(); ++c_itr)
		{
			if (c_itr->isArray())
			{
				category_order_.push_back(c_itr.key());
				QJsonArray doc_array = c_itr->toArray();
				auto &category = all_password_data_[c_itr.key()];

				emit categoryCreated(c_itr.key());

				for (size_t index = 0; index < doc_array.size(); ++index)
				{
					PassWordData data;
					QJsonObject doc = doc_array[index].toObject();
					data.title = doc["title"].toString();		
					data.user_name = doc["user_name"].toString();
					data.pass_word = doc["pass_word"].toString();
					data.url = doc["url"].toString();
					data.notes = doc["notes"].toString();
					category.push_back(std::move(data));

					emit documentCreated(category_order_.size() - 1, category.back());
				}
			}
		}
	}
}

bool DataSource::hasCategory(const QString &name)
{
	return all_password_data_.find(name) != all_password_data_.end();
}

bool DataSource::deleteCategory(const size_t index)
{
	if (index < all_password_data_.size())
	{
		auto itr = all_password_data_.find(category_order_[index]);
		all_password_data_.erase(itr);
		emit categoryDeleted(index);
		return true;
	}
	return false;
}

bool DataSource::createCategory(const QString &name)
{
	if (!hasCategory(name))
	{
		category_order_.push_back(name);
		all_password_data_.insert(name, QVector<PassWordData>());
		emit categoryCreated(name);
		return true;
	}
	return false;
}

bool DataSource::modifieCategory(const size_t index, const QString &new_name)
{
	if (index < all_password_data_.size() && !hasCategory(new_name))
	{
		auto itr = all_password_data_.find(category_order_[index]);
		QVector<PassWordData> temp(std::move((*itr)));
		all_password_data_.erase(itr);
		category_order_[index] = new_name;
		all_password_data_.insert(new_name, std::move(temp));
		emit categoryModified(index, new_name);
		return true;
	}
	return false;
}

bool DataSource::deleteDocument(const size_t category_index, const size_t doc_index)
{
	if (category_index < all_password_data_.size())
	{
		auto itr = all_password_data_.find(category_order_[category_index]);
		if (doc_index < itr->size())
		{
			itr->erase(itr->begin() + doc_index);
			emit deleteDocument(category_index, doc_index);
			return true;
		}
	}
	return false;
}

bool DataSource::createDocument(const size_t category_index, const PassWordData &doc)
{
	if (category_index < all_password_data_.size())
	{
		auto itr = all_password_data_.find(category_order_[category_index]);
		itr->push_back(doc);
		emit documentCreated(category_index, doc);
		return true;
	}
	return false;
}

bool DataSource::modifieDocument(const size_t category_index, const size_t doc_index, const PassWordData &doc)
{
	if (category_index < all_password_data_.size())
	{
		auto itr = all_password_data_.find(category_order_[category_index]);
		if (doc_index < itr->size())
		{
			itr->operator[](doc_index) = doc;
			emit modifieDocument(category_index, doc_index, doc);
			return true;
		}
	}
	return false;
}